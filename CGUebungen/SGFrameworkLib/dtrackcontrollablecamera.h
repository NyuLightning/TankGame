#ifndef DTRACKCONTROLLABLECAMERA_H
#define DTRACKCONTROLLABLECAMERA_H
#include "controllablecamera.h"


class DTrackControllableCamera : public ControllableCamera
{
public:
    DTrackControllableCamera(QString device);

    virtual void doIt() override;
private:
    QString m_device;

};

#endif // DTRACKCONTROLLABLECAMERA_H
