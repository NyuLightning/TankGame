#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <drawable.h>
#include <transformation.h>



class Projectile
{
    PhysicEngine* _phyEngine;
    Geometry* _geometry;
    Drawable* _drawable;
    Transformation* _transformation;
    PhysicObject* _phyObj;
    Node* _Node;


public:
    Projectile(PhysicEngine* physicEngine);

    Node* getNode();
};

#endif // PROJECTILE_H
