#include "vrpndevicedtrack.h"
#include <QDebug>
#include "vrpn_Analog.h"
#include "vrpn_Button.h"
#include "vrpn_Tracker.h"
#include "inputregistry.h"

VRPNDeviceDTrack *VRPNDeviceDTrack::m_Instance = 0;

void VRPN_CALLBACK handleAnalog(void *a_UserData, const vrpn_ANALOGCB a_Analog)
{
    (void)a_UserData;
    AnalogInfo v_JoystickInfo;
    for (int i = 0; i < a_Analog.num_channel && i < 2; i += 1)
    {
        v_JoystickInfo.m_Axis[i] = (float)(a_Analog.channel[i]);
    }
    VRPNDeviceDTrack::getInstance()->setJoystickInfo(v_JoystickInfo);
}

void VRPN_CALLBACK handleButtons(void *a_UserData, const vrpn_BUTTONCB a_Button)
{
    (void)a_UserData;
    if (a_Button.button < 8)
    {
        VRPNDeviceDTrack::getInstance()->setButton(a_Button.button, (bool)a_Button.state);
    }
}

TrackerInfo toTrackerInfo(const vrpn_TRACKERCB a_Tracker)
{
    TrackerInfo v_Data;

    v_Data.m_Position[0] = (float)(a_Tracker.pos[1]);
    v_Data.m_Position[1] =
        (float)(a_Tracker.pos[2] +
                0.655f);  // World Coordinate System is 65,5 cm higher than the real world
    v_Data.m_Position[2] = (float)(a_Tracker.pos[0]);

    v_Data.m_Quaternion[0] = (float)(a_Tracker.quat[3]);
    v_Data.m_Quaternion[1] = (float)(a_Tracker.quat[1]);
    v_Data.m_Quaternion[2] = (float)(a_Tracker.quat[2]);
    v_Data.m_Quaternion[3] = (float)(a_Tracker.quat[0]);

    return v_Data;
}

void VRPN_CALLBACK handleTracker(void *a_UserData, const vrpn_TRACKERCB a_Tracker)
{
    (void)a_UserData;
    if (a_Tracker.sensor == 0)
    {
        VRPNDeviceDTrack::getInstance()->setHeadPosition(toTrackerInfo(a_Tracker));
    }
    else if (a_Tracker.sensor == 1)
    {
        VRPNDeviceDTrack::getInstance()->setFlightStickPosition(toTrackerInfo(a_Tracker));
    }
}

VRPNDeviceDTrack::VRPNDeviceDTrack()
    : m_Buttons{false, false, false, false, false, false, false, false}
{
    m_ButtonInfo.m_ButtonPressed = 0;
    m_JoystickInfo.m_Axis[0] = 0.f;
    m_JoystickInfo.m_Axis[1] = 0.f;

    m_FlightStickPos.m_Position[0] = 0.f;
    m_FlightStickPos.m_Position[1] = 0.f;
    m_FlightStickPos.m_Position[2] = 0.f;
    m_FlightStickPos.m_Quaternion[0] = 0.f;
    m_FlightStickPos.m_Quaternion[1] = 0.f;
    m_FlightStickPos.m_Quaternion[2] = 0.f;
    m_FlightStickPos.m_Quaternion[3] = 0.f;

    m_HeadPos.m_Position[0] = 0.f;
    m_HeadPos.m_Position[1] = 0.f;
    m_HeadPos.m_Position[2] = 0.f;
    m_HeadPos.m_Quaternion[0] = 0.f;
    m_HeadPos.m_Quaternion[1] = 0.f;
    m_HeadPos.m_Quaternion[2] = 0.f;
    m_HeadPos.m_Quaternion[3] = 0.f;

    m_Analog = new vrpn_Analog_Remote("DTrack@localhost");
    m_Button = new vrpn_Button_Remote("DTrack@localhost");
    m_Tracker = new vrpn_Tracker_Remote("DTrack@localhost");

    m_Analog->register_change_handler(0, handleAnalog);
    m_Button->register_change_handler(0, handleButtons);
    m_Tracker->register_change_handler(0, handleTracker);
}

void VRPNDeviceDTrack::doIt()
{
    m_Analog->mainloop();
    m_Button->mainloop();
    m_Tracker->mainloop();
}

VRPNDeviceDTrack::~VRPNDeviceDTrack()
{
    delete m_Analog;
    delete m_Button;
    delete m_Tracker;
}

VRPNDeviceDTrack *VRPNDeviceDTrack::getInstance()
{
    if (!m_Instance) m_Instance = new VRPNDeviceDTrack;
    return m_Instance;
}

AnalogInfo &VRPNDeviceDTrack::getJoystickInfo()
{
    m_Analog->mainloop();
    return m_JoystickInfo;
}

ButtonInfo &VRPNDeviceDTrack::getButtonInfo()
{
    m_Button->mainloop();
    return m_ButtonInfo;
}

TrackerInfo &VRPNDeviceDTrack::getHeadPosition()
{
    m_Tracker->mainloop();
//        qDebug()<<"Head XYZ:"<<m_HeadPos.m_Position[0]<<" "<<m_HeadPos.m_Position[1]<<" "<<m_HeadPos.m_Position[2];
    return m_HeadPos;
}

TrackerInfo &VRPNDeviceDTrack::getFlightStickPosition()
{
    m_Tracker->mainloop();
//     qDebug()<<"Flightstick XYZ:"<<m_FlightStickPos.m_Position[0]<<m_FlightStickPos.m_Position[1]<<" "<<m_FlightStickPos.m_Position[2];
    return m_FlightStickPos;
}

void VRPNDeviceDTrack::setButton(int button, bool state)
{
    m_Buttons[button] = state;

        state ? InputRegistry::getInstance().getFlystickInput()->setFsButtonDown(button)
              : InputRegistry::getInstance().getFlystickInput()->setFsButtonUp(button);

}

void VRPNDeviceDTrack::setJoystickInfo(AnalogInfo a_JoystickInfo)
{
    m_JoystickInfo = a_JoystickInfo;
    if (InputRegistry::getInstance().hasFlystickInput())
    {
        int x = 100 * a_JoystickInfo.m_Axis[0];
        int y = 100 * a_JoystickInfo.m_Axis[1];
        InputRegistry::getInstance().getFlystickInput()->setFsAnalogstickPos(QPoint(x, y));
    }
}

void VRPNDeviceDTrack::setButtonInfo(ButtonInfo a_ButtonInfo) { m_ButtonInfo = a_ButtonInfo; }
void VRPNDeviceDTrack::setHeadPosition(TrackerInfo a_TrackerInfo)
{
    m_HeadPos = a_TrackerInfo;
    if (InputRegistry::getInstance().hasTrackingInput())
    {
        InputRegistry::getInstance().getTrackingInput()->setTrViewDirection(
            QQuaternion(m_HeadPos.m_Quaternion[0], m_HeadPos.m_Quaternion[1],
                        m_HeadPos.m_Quaternion[2], m_HeadPos.m_Quaternion[3]));
        InputRegistry::getInstance().getTrackingInput()->setTrHeadPos(
            QVector3D(m_HeadPos.m_Position[0], m_HeadPos.m_Position[1], m_HeadPos.m_Position[2]));
    }
}
void VRPNDeviceDTrack::setFlightStickPosition(TrackerInfo a_TrackerInfo)
{

    m_FlightStickPos = a_TrackerInfo;
    InputRegistry::getInstance().getFlystickInput()->setFsPos(QVector3D(
        m_FlightStickPos.m_Position[0],
        m_FlightStickPos.m_Position[1],
        m_FlightStickPos.m_Position[2]));
    InputRegistry::getInstance().
            getFlystickInput()->setFsOrientation(QQuaternion(
            m_FlightStickPos.m_Quaternion[0], m_FlightStickPos.m_Quaternion[1],
            m_FlightStickPos.m_Quaternion[2],m_FlightStickPos.m_Quaternion[3]
                ));
}
