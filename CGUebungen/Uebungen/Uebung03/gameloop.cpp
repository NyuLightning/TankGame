#include "gameloop.h"

GameLoop::GameLoop(Transformation* body, Transformation* turret,
                   Transformation* barrel, Camera* cam, Node* rootNode, PhysicEngine* phyEngine)
{
    //nicht direkt schießen können, da buggy
    lastFiredTime = QTime::currentTime();
    bool hasFired = true;

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
            turretMatrix.flipCoordinates();
            //QMatrix4x4 barrelMatrix = barrel->getModelMatrix();
            //QMatrix4x4 combinedmatrix = turretMatrix*barrelMatrix;
            //combinedmatrix.flipCoordinates();

            Projectile* bullet = new Projectile(phyEngine, turretMatrix, rootNode);
        }        
    }



    // ///////////////////////////

    // modelMatrix enthält position und translation. Position ist vierte Spalte mit skalierung als viertes element.
    QMatrix4x4 posMatrix = turret->getModelMatrix();
    QVector3D pos = posMatrix.column(3).toVector3DAffine(); //remove "Affine" if scaling makes trouble

    cam->setEyePosition(pos);


    //turret Rotation an Kamera anpassen,
    //geht nicht, da MouseContollableCamera auch über keyboard gesteuert werden kann
//    QVector3D forward = cam->getDir().normalized();
//    QVector3D up = QVector3D(-forward.x()*forward.y(),
//                                (forward.x()*forward.x())+(forward.z()*forward.z()),
//                                -forward.y()*forward.z());
//    QVector3D right = QVector3D::crossProduct(up,forward);
//    up = up.normalized();
//    right = right.normalized();

//    QMatrix4x4 CameraRotationMatrix;1
//    CameraRotationMatrix.setColumn(0,QVector4D(right,1));
//    CameraRotationMatrix.setColumn(1,QVector4D(up,1));
//    CameraRotationMatrix.setColumn(2,QVector4D(forward,1));
//    CameraRotationMatrix.setColumn(3,QVector4D(pos,1));

    //turret->setModelMatrix(CameraRotationMatrix);

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
