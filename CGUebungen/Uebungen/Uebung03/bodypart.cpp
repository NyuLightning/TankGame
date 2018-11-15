/*
 *  BodyPart.cpp
 *  robot
 *
 *  Created by bdr on 12.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#include "bodypart.h"

#include "scenemanager.h"

BodyPart::BodyPart()
{
    sx = sy = sz = 1.0;
    init();
}

BodyPart::BodyPart(float ssx, float ssy, float ssz) : Drawable(new SimpleCube(ssx, ssy, ssz))
{
    sx = ssx;
    sy = ssy;
    sz = ssz;
    init();
}

float BodyPart::getX()
{
    return sx;
}
float BodyPart::getY()
{
    return sy;
}
float BodyPart::getZ()
{
    return sz;
}

void BodyPart::setPosition(float x, float y, float z)
{
    mTrafo->resetTrafo();
    mTrafo->translate(x, y, z);
}

void BodyPart::beforeTraverseChilds(SGObjectVisitor& visitor)
{
    mTrafo->activate();
    Drawable::beforeTraverseChilds(visitor);
}

void BodyPart::afterTraverseChilds()
{
    mTrafo->deActivate();
}

void BodyPart::init()
{
    mTrafo = new Transformation;
}
