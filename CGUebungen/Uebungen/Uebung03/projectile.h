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
    Node* _Node;

    QString path;


public:
    Projectile(PhysicEngine* physicEngine, QVector3D direction);

    Node* getNode();
};

#endif // PROJECTILE_H
