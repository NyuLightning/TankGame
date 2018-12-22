#include "gameloop.h"


GameLoop::GameLoop(Transformation* body, Transformation* turret, Transformation* barrel)
{
    //Panzer Transformations referenzen im GameLoop speichern
    this->chassis = body;
    this->turret = turret;
    this->barrel = barrel;



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
}
void GameLoop::doIt(){

    // Keybord Input, kann mehrere Inputs gleichzeitig verarbeiten, daher keine 'if else' oder switch verwenden!
    KeyboardInput* keyIn = InputRegistry::getInstance().getKeyboardInput();

    if (keyIn->isKeyPressed('a'))
    {
        // Hochschieben, um an der Schulter und nicht am Mittelpunkt zu drehen
        // trafo->translate(0.0, -1.6 , 0.0);
        chassis->rotate(0.1f*chassisSensitivity, 0.0f, 1.0f,0.0f);
        // Danach wieder runterschieben
        // trafo->translate(0.0, 1.6 , 0.0);
    }
    if (keyIn->isKeyPressed('d'))
    {
        chassis->rotate(-0.1f*chassisSensitivity, 0.0f, 1.0f,0.0f);
    }

    //turret (isKeyPressed nutzt das Qt Framework für Tasten. Alle unter QT::Key_* zu finden
    if (keyIn->isKeyPressed(Qt::Key_Left))
    {
        turret->rotate(0.1f*turretSensitivity, 0.0f, 1.0f,0.0f);
    }
    if (keyIn->isKeyPressed(Qt::Key_Right))
    {
        turret->rotate(-0.1f*turretSensitivity, 0.0f, 1.0f,0.0f);
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

    // Vorwärts + Rückw#rts
    if (keyIn->isKeyPressed('w'))
    {

    }
    if (keyIn->isKeyPressed('s'))
    {


    }

    //non GamePlay keys
    if (keyIn->isKeyPressed(Qt::Key_Escape))
    {

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
