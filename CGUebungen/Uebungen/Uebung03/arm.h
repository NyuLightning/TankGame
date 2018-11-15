/*
 *  arm.h
 *  robot
 *
 *  Created by bdr on 12.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#ifndef _ARM_H_
#define _ARM_H_

#include "bodypart.h"
#include "listener.h"

class Arm : public BodyPart, public Listener
{
private:
    bool rechts;

public:
    Arm();
    Arm(float sx, float sy, float sz, bool r) : BodyPart(sx, sy, sz)
    {
        rechts = r;
    }
    virtual void keyboard(int key, int modifier);
};

#endif
