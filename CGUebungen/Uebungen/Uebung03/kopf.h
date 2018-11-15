/*
 *  kopf.h
 *  robot
 *
 *  Created by bdr on 12.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#ifndef _KOPF_H_
#define _KOPF_H_

#include "bodypart.h"
#include "listener.h"

//! Eigene Klasse für Kopf.
/// Eigene Klassen sind hier eigentlich nur notwendig, weil man verschiedene Keys verwenden möchte.
/// Alternativ könnte man diese Klasse und die Arm-Klasse weglassen und stattdessen eigene
/// KeyboardTransformation-Elemente in den Graphen einfügen.
class Kopf : public BodyPart, public Listener
{
public:
    Kopf();
    Kopf(float sx, float sy, float sz) : BodyPart(sx, sy, sz)
    {
    }
    virtual void keyboard(int key, int modifier);
};

#endif
