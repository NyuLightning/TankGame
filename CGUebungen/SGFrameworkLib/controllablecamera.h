#ifndef CONTROLLABLECAMERA_H
#define CONTROLLABLECAMERA_H

#include "camera.h"
#include "idleobserver.h"

//! Eine Kamera, die eine klassische Kamerasteuerung über a, s, d, w, den Cursortasten sowie x, y, z
//! für eine
//! Drehung um die Hauptachsen erlaubt.
class ControllableCamera : public Camera, public IdleObserver
{
   public:
    ControllableCamera();

    virtual void doIt() override;
};

#endif  // CONTROLLABLECAMERA_H
