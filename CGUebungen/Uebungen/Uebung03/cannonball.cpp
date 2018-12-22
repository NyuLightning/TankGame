#include "cannonball.h"

const float fallbeschleunigung = 9.81f;

Cannonball::Cannonball()
{
    fire();
}
void Cannonball::fire()
{
    SimpleSphere* sCannonball = new SimpleSphere(1.0,1.0,1.0);
    Drawable* theCannonball = new Drawable(sCannonball);

    Color* c;
    c = theCannonball->getProperty<Color>();
    c->setValue(1.0f, 1.0f, 0.0f, 1.0f);

    Transformation* theCannonballTranslation = new Transformation();
    theCannonballTranslation->translate(1.0,1.0,1.0); // Vorderer Punkt vom Rohr bekommen

    QVector3D* positionAtNull = new QVector3D(); // Spitze Rohr Position auslesen
    QVector3D* positionAtTime = new QVector3D(); // init mit gleichen Werten^^^^
    QVector3D* velocityAtNull = new QVector3D(); //
    QVector3D* acceleration = new QVector3D(0.0, -fallbeschleunigung, 0.0); //Sollte ich zwei Vektoren machen, einen vor Halbzeit, einen danach oder wie muss ich mir das vorstellen?
    int duration = 300; //Wert mus erst ausgerechnet werden

    for (int time = 1; time <= duration; time++)
    {
        positionAtTime = positionAtNull + velocityAtNull * time + 0.5 * acceleration * (time * time); // Kann man QVector nicht skalarmultiplizieren?
        theCannonballTranslation->translate(positionAtTime->x(), positionAtTime->y(), positionAtTime->z());
    }
}
