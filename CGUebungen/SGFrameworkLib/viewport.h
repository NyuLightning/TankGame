#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "opengl.h"
#include <qdebug.h>

//! Diese Klasse setzte die OpenGL Viewports. Für jede
//! Projektionsmatrix wird eine neue Instanz dieser Klasse erzeugt.

class Viewport
{
public:
    Viewport();  

    //! Setzt die Dimensionen des Ausgabefensterns
    void reshape(int viewportWidth, int viewportHeight);

    //!Setzen des Viewports für 2D Rendering
    void setViewport2D(int index);

    //!Setzen des Viewports für 3D Rendering
    void setViewport3D(int index, int pos);

private:
    float m_viewportWidth;
    float m_viewportHeight;
};

#endif // VIEWPORT_H
