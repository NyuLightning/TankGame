#ifndef VRPNDEVICES_H
#define VRPNDEVICES_H
//#include "idleobserver.h"

#define BIT(n) 1<<n
enum Buttons
{
    Button0=BIT(0),//Trigger
    Button1=BIT(1),//First from Right
    Button2=BIT(2),//Second from Right
    Button3=BIT(3),//Third from Right
    Button4=BIT(4),//Fourth from Right
    Button5=BIT(5),//Analog Button
    Button6=BIT(6),
    Button7=BIT(7)
};
#undef BIT

struct AnalogInfo{
    float m_Axis[2]; // Axis of flight stick range -1,1// First float X-Axis: Left: -1 Right:+1 //Second float Y-Axis: Up:+1 Down:-1
};

struct ButtonInfo{
    char m_ButtonPressed; //1 bits button pressed, 0 bits button not pressed
};

struct TrackerInfo{
    float m_Position[3]; //position x,y,z
    float m_Quaternion[4]; //orientation as quaternion, (scalar,x,y,z)
};

//Forward Declaration to avoid includes in header
class VRPNDeviceDTrack;
class vrpn_Analog_Remote;
class vrpn_Button_Remote;
class vrpn_Tracker_Remote;

class VRPNDeviceDTrack
{
private:
    VRPNDeviceDTrack();
public:
    virtual void doIt();

    virtual ~VRPNDeviceDTrack();
    static VRPNDeviceDTrack* getInstance();
    AnalogInfo &getJoystickInfo();
    ButtonInfo &getButtonInfo();

    TrackerInfo &getHeadPosition();
    TrackerInfo &getFlightStickPosition();

    void setButton(int button, bool state);
    void setJoystickInfo(AnalogInfo a_JoystickInfo);
    void setButtonInfo(ButtonInfo a_ButtonInfo);
    void setHeadPosition(TrackerInfo a_TrackerInfo);
    void setFlightStickPosition(TrackerInfo a_TrackerInfo);
private:
    static VRPNDeviceDTrack* m_Instance;

    bool m_JoystickInfoChanged;
    bool m_ButtonInfoChanged;
    bool m_HeadPosChanged;
    bool m_FlightStickPosChanged;

    vrpn_Analog_Remote *m_Analog;
    vrpn_Button_Remote *m_Button;
    vrpn_Tracker_Remote *m_Tracker;

    bool m_Buttons[8];
    AnalogInfo m_JoystickInfo;
    ButtonInfo m_ButtonInfo;
    TrackerInfo m_HeadPos;
    TrackerInfo m_FlightStickPos;
};

#endif // VRPNDEVICES_H
