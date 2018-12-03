#ifndef BODY_H
#define BODY_H

#include "transformation.h"
#include "listener.h"
#include "bodypart.h"

class Body : public Listener, public BodyPart
{
private:
    bool rechts;

public:
    Body();
    Body(float sx, float sy, float sz, bool r) : BodyPart(sx, sy, sz)
        {
            rechts = r;
        }
    virtual void keyboard(int key, int modifier);

};

#endif
