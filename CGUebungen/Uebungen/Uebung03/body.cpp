#include "body.h"

#include "transformation.h"
#include "inputregistry.h"
#include "trianglemesh.h"
#include "listener.h"

Body::Body()
{
    QString path(SRCDIR);
    Geometry* gBody = new TriangleMesh(path + QString("/../Models/body.obj"));
    Drawable* dBody = new Drawable(gBody);

}

void Body::keyboard(int key, int /*modifier*/)
{
    KeyboardInput* keyIn = InputRegistry::getInstance().getKeyboardInput();

    Transformation& trafo = this->getTrafo();
    int lMyKey = rechts? 'v':'c';

    if (keyIn->isKeyPressed(lMyKey))
    {
        // Hochschieben, um an der Schulter und nicht am Mittelpunkt zu drehen
        trafo.translate(0.0, this->getY() / 2, 0.0);
        trafo.rotate(5.0, 1.0, 0.0, 0.0);
        // Danach wieder runterschieben
        trafo.translate(0.0, -this->getY() / 2, 0.0);
     }
    if (keyIn->isKeyPressed(toupper(lMyKey)))
    {
        trafo.translate(0.0, this->getY() / 2, 0.0);
        trafo.rotate(-5.0, 1.0, 0.0, 0.0);
        trafo.translate(0.0, -this->getY() / 2, 0.0);
    }
}
