#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <drawable.h>
#include <transformation.h>



class Projectile
{

    float _projectileSpeed;

    PhysicEngine* _phyEngine;
    Geometry* _geometry;
    Drawable* _drawable;
    Transformation* _transformation;
    PhysicObject* _phyObj;   

    QString path;


public:
    Projectile(PhysicEngine* physicEngine, QMatrix4x4 turretMatrix, Node* rootNode);
};

#endif // PROJECTILE_H
