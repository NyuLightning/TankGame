#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <drawable.h>
#include <transformation.h>

class EnemyTank
{
    PhysicEngine* _phyEngine;

    Geometry* chassis_geometry;
    Drawable* chassis_drawable;
    Transformation* chassis_transformation;
    PhysicObject* chassis_phyObj;

    Geometry* barrel_geometry;
    Drawable* barrel_drawable;
    Transformation* barrel_transformation;
    PhysicObject* barrel_phyObj;

    Geometry* turret_geometry;
    Drawable* turret_drawable;
    Transformation* turret_transformation;
    PhysicObject* turret_phyObj;

    QString path;

public:
    EnemyTank(PhysicEngine* physicEngine, QMatrix4x4 StartPosMatrix, Node* rootNode);
};

#endif // ENEMYTANK_H
