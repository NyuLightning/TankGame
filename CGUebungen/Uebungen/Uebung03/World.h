#ifndef WORLD_H
#define WORLD_H

#include "drawable.h"
#include "simplecube.h"
#include "transformation.h"

class World: public Drawable
{
public:
    World();
    World(float, float, float);
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

inline Transformation& World::getTrafo()
{
    return *mTrafo;
};


#endif // WORLD_H
