//#include "cannonball.h"

//const float fallbeschleunigung = 9.81f;

///*


//     Formeln: http://farside.ph.utexas.edu/teaching/301/lectures/node34.html
//              https://www.physicsforums.com/threads/projectile-range-equation-in-3d-space.325772/


//*/

//Cannonball::Cannonball(float angleShot)
//{
//    positionAtNull = new QVector3D(); // Spitze Rohr Position auslesen
//    positionAtTime = new QVector3D(); // init mit gleichen Werten^^^^

//    //velocityBeginning = ; // Geschwindigkeit am Anfang nicht als Vektor
//    //duration = calculateTime();

//    acceleration = new QVector3D(0.0, 0.0, -fallbeschleunigung);
//    this->angle = angleShot; // Hier Winkel aus dem gefeuert wird bekommen

//    velocityAtNull = new QVector3D();
//    calculateVelocity();



//    fire();
//}

//void Cannonball::fire()
//{
//    SimpleSphere* sCannonball = new SimpleSphere(1.0,1.0,1.0);
//    Drawable* theCannonball = new Drawable(sCannonball);

//    Color* c;
//    c = theCannonball->getProperty<Color>();
//    c->setValue(1.0f, 1.0f, 1.0f, 1.0f);

//    Transformation* theCannonballTranslation = new Transformation();
//    theCannonballTranslation->translate(positionAtNull->x(), positionAtNull->y(), positionAtNull->z());

//    for(int time = 1; time <= duration; time++)
//    {
//        calculateDisplacementVector(time);
//        theCannonballTranslation->translate(positionAtTime->x(), positionAtTime->y(), positionAtTime->z());
//    }
//}

//void Cannonball::calculateVelocity()
//{
//    velocityAtNull->setX(velocityBeginning * cos(angle));
//    velocityAtNull->setY(0);
//    velocityAtNull->setZ(velocityBeginning * sin(angle));
//}

//void Cannonball::calculateDisplacementVector(int timeElapsed)
//{
//    positionAtTime->setX(velocityAtNull->x() * timeElapsed);
//    positionAtTime->setY(0);
//    positionAtTime->setZ(velocityAtNull->z() * timeElapsed - 0.5f * fallbeschleunigung * (timeElapsed * timeElapsed));
//}

////int Cannonball::calculateTime()
////{
////    duration = ((2.0f*velocityBeginning)/fallbeschleunigung);
////}
