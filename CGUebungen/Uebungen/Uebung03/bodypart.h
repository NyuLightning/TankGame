/*
 *  BodyPart.h
 *  robot
 *
 *  Created by bdr on 12.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#ifndef _BodyPart_H_
#define _BodyPart_H_

#include "drawable.h"
#include "simplecube.h"
#include "transformation.h"

//! Basisklasse (Darstellung von skalierten Quadern) für alle Körperteile des Robby
class BodyPart : public Drawable
{
public:
    BodyPart();
    BodyPart(float, float, float);
    //! X-Skalierung
    float getX();
    //! Y-Skalierung
    float getY();
    //! Z-Skalierung
    float getZ();
    void setPosition(float x, float y, float z);

    virtual void beforeTraverseChilds(SGObjectVisitor& visitor) override;
    virtual void afterTraverseChilds() override;

protected:
    inline Transformation& getTrafo();

private:
    void init();

    float sx, sy, sz; // Groessenangaben fuer den zu zeichnenden Quader
    Transformation* mTrafo;
};

inline Transformation& BodyPart::getTrafo()
{
    return *mTrafo;
}

#endif
