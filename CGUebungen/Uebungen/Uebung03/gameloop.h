#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "idleobserver.h"
#include "transformation.h"
#include "inputregistry.h"
#include <QVector3D>


class GameLoop : public IdleObserver
{
    float chassisSensitivity;
    float turretSensitivity;
    float barrelSensitivity;

    //Kanonenrohr kann nicht beliebig weit rotieren
    float barrelMaxTraverseUp;
    float barrelMaxTraverseDown;

    float barrelCurrentTraverseAngle;

    QVector3D pipeOffset;
    QVector3D turretOffset;

    Transformation* chassis;
    Transformation* turret;
    Transformation* barrel;

public:
    GameLoop(Transformation* chassis, Transformation* turret, Transformation* barrel);
    void doIt();
    void SetSensitivity(float chassisS, float turretS, float barrelS);
    void SetBarrelLimits(float maxUp, float maxDown);
    void SetOffsets(QVector3D pipeOffset, QVector3D turretOffset);
};

#endif // GAMELOOP_H
