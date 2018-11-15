/*
 *  kopf.cpp
 *  robot
 *
 *  Created by bdr on 12.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#include "transformation.h"
#include "kopf.h"

void Kopf::keyboard(int key, int /*modifier*/)
{
    Transformation& trafo = this->getTrafo();
    switch (key)
    {
    case 'k':
        trafo.rotate(5.0, 0.0, 1.0, 0.0);
        break;
    case 'K':
        trafo.rotate(-5.0, 0.0, 1.0, 0.0);
        break;
    }
}
