#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "idleobserver.h"
#include "transformation.h"
#include "inputregistry.h"
#include "camera.h"
#include "projectile.h"
#include <QTime>


class GameLoop : public IdleObserver
{
    //schussProSekunde limitierung
    QTime lastFiredTime;
    bool hasFired;

    //Root Node um Kugeln einzuhängen
    Node* rootNode;

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

    //Turm Orientierung/position tracker
    QVector3D turretRotation;
    QVector3D turretPosition;

    Camera* cam;
    PhysicEngine* phyEngine;


public:
    GameLoop(Transformation* chassis, Transformation* turret, Transformation* barrel, Camera* cam, Node* rootNode, PhysicEngine* phyEngine);
    void doIt();
    void SetSensitivity(float chassisS, float turretS, float barrelS);
    void SetBarrelLimits(float maxUp, float maxDown);
    void SetOffsets(QVector3D pipeOffset, QVector3D turretOffset);
};

#endif // GAMELOOP_H
