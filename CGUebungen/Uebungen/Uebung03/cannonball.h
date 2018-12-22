#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "simplesphere.h"
#include "drawable.h"
#include "transformation.h"
#include <color.h>
#include "QVector3D"

class Cannonball: public Drawable
{
public:
    Cannonball();
    ~Cannonball();
    void fire();
};

#endif // CANNONBALL_H
