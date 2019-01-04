#include "gameloop.h"
#include <QRandomGenerator>

GameLoop::GameLoop(Transformation* body, Transformation* turret,
                   Transformation* barrel, Camera* cam, Node* rootNode, PhysicEngine* phyEngine)
{
    //nicht direkt schießen können, da buggy
    lastFiredTime = QTime::currentTime();
    bool hasFired = true;

    enemySpawned = QTime::currentTime();

    //Panzer Transformations referenzen im GameLoop speichern
    this->chassis = body;
    this->turret = turret;
    this->barrel = barrel;
    this->cam = cam;
    this->rootNode = rootNode;
    this->phyEngine = phyEngine;

    //Initialisieren
    chassisSensitivity = 0.8;
    turretSensitivity = 1;
    barrelSensitivity = 0.5f;

    barrelMaxTraverseUp = 20;
    barrelMaxTraverseDown = -7;
    barrelCurrentTraverseAngle = 0;

    pipeOffset = QVector3D(0,0,0);
    turretOffset = QVector3D(0,0,0);

    // Teile auf Anfangsposition bringen
    turret->translate(0, 2, 0);
    barrel->translate(0, 0, 1.8);
    cam->rotate(180,0,0);
}
void GameLoop::doIt(){

    // Keybord Input, kann mehrere Inputs gleichzeitig verarbeiten, daher keine 'if else' oder switch verwenden!
    KeyboardInput* keyIn = InputRegistry::getInstance().getKeyboardInput();


    if (keyIn->isKeyPressed('w'))
    {
        chassis->translate(0.0f, 0.0f,0.003f);
    }
    if (keyIn->isKeyPressed('s'))
    {
          chassis->translate(0.0f, 0.0f,-0.003f);
    }
    if (keyIn->isKeyPressed('a'))
    {      
        chassis->rotate(0.1f*chassisSensitivity, 0.0f, 1.0f,0.0f);
        turret->rotate(-0.1f*chassisSensitivity, 0.0f, 1.0f,0.0f); //turm bleibt stehen wenn wanne sich dreht
    }
    if (keyIn->isKeyPressed('d'))
    {
        chassis->rotate(-0.1f*chassisSensitivity, 0.0f, 1.0f,0.0f);
        turret->rotate(0.1f*chassisSensitivity, 0.0f, 1.0f,0.0f);
    }

    //turret (isKeyPressed nutzt das Qt Framework für Tasten. Alle unter QT::Key_* zu finden
    if (keyIn->isKeyPressed(Qt::Key_Left))
    {
        turret->rotate(0.1f*turretSensitivity, 0.0f, 1.0f,0.0f);
        cam->rotate(-0.1f*turretSensitivity, 0.0f, 0.0f);
    }
    if (keyIn->isKeyPressed(Qt::Key_Right))
    {
        turret->rotate(-0.1f*turretSensitivity, 0.0f, 1.0f,0.0f);
        cam->rotate(0.1f*turretSensitivity, 0.0f, 0.0f);
    }

    //barrel, wird durch Winkelangaben Limitiert
    if (keyIn->isKeyPressed(Qt::Key_Up))
    {
        if(barrelCurrentTraverseAngle < barrelMaxTraverseUp){
            barrel->rotate(-0.1f*barrelSensitivity, 1.0f,0.0f,0.0f);            
            barrelCurrentTraverseAngle += 0.1f*barrelSensitivity;
        }
    }
    if (keyIn->isKeyPressed(Qt::Key_Down))
    {
        if(barrelCurrentTraverseAngle > barrelMaxTraverseDown){
            barrel->rotate(0.1f*barrelSensitivity, 1.0f,0.0f,0.0f);            
            barrelCurrentTraverseAngle -= 0.1f*barrelSensitivity;
        }
    }

    if (keyIn->isKeyPressed(Qt::Key_Space))
    {
        QTime currentTime = QTime::currentTime();

        if(currentTime > lastFiredTime.addSecs(2)){
            hasFired = true;
            lastFiredTime = QTime::currentTime();

            QMatrix4x4 turretMatrix = turret->getModelMatrix();            
            QMatrix4x4 chassisMatrix = chassis->getModelMatrix();
            turretMatrix.flipCoordinates();

            QMatrix4x4 ma = chassisMatrix * turretMatrix;


            Projectile* bullet = new Projectile(phyEngine, ma, rootNode);
        }        
    }



    // ///////////////////////////

    // modelMatrix enthält position und translation. Position ist vierte Spalte mit skalierung als viertes element.
    QMatrix4x4 posMatrix = chassis->getModelMatrix();
    QVector3D pos = posMatrix.column(3).toVector3DAffine(); //remove "Affine" if scaling makes trouble
    cam->setEyePosition(pos);

    if(QTime::currentTime() > enemySpawned.addSecs(5)){
        enemySpawned = QTime::currentTime();
        QMatrix4x4 startPos = chassis->getModelMatrix();

        int x = QRandomGenerator::global()->bounded(-20,20);
        int z = QRandomGenerator::global()->bounded(-20,20);
        startPos.translate(x,0,z);

        EnemyTank* enemy = new EnemyTank(phyEngine, startPos, rootNode);
    }

}
void GameLoop::SetSensitivity(float chassisS, float turretS, float barrelS){
    chassisSensitivity = chassisS;
    turretSensitivity = turretS;
    barrelSensitivity = barrelS;
}
void GameLoop::SetBarrelLimits(float maxUp, float maxDown){
    barrelMaxTraverseUp = maxUp;
    barrelMaxTraverseDown = maxDown;
}
void GameLoop::SetOffsets(QVector3D pipeOffset, QVector3D turretOffset){
    this->pipeOffset = pipeOffset;
    this->turretOffset = turretOffset;
}
