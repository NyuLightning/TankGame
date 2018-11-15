#ifndef FBOPROPERTY_H
#define FBOPROPERTY_H

#include "fborenderer.h"

//! Eine Property, die eine mittels FrameBufferObjects erzeugte Textur an ein Drawable bindet. FBOProperty verhält sich
//! fast wie eine Textur an sich, allerdings gehört ein Objekt dieser Klasse immer zu einem FBORenderer, der die
//! jeweilige Textur erzeugt.
//! Wenn der Renderer aktiv ist, wird das zur Property gehörende Drawable nicht gerendert. Dies deswegen, weil bei Environment-Maps
//! und ähnlichen Techniken das Drawable das gewünschte Ergebnis schlicht verdecken würde.
class FBOProperty : public DrawableProperty
{
public:
    FBOProperty();
    virtual ~FBOProperty();
    virtual void init(Node *renderTree, float boxSize, Drawable* ownerDrawable, int texDim = GL_TEXTURE_2D, int unit = 3, int pRes = 512);
    void turnOff(Shader* shader) override;
    void turnOn(Shader* shader) override;
    static DrawablePropertyId getPropertyId() {return DrawablePropertyIdGeter::getIdOf<FBOProperty>();}
    virtual DrawablePropertyId getId() const override;

protected:
    //! Größe der Box für das Rendering
    float mBoxSize;
    int mWidth, mHeight;
    int mTexDim;
    int mTextureUnit;
    GLuint mTexID;
    FBORenderer* mRenderer;

private:
    void release();
};

//inline DrawablePropertyId FBOProperty::getPropertyId()
//{
//    return DrawablePropertyIdGeter::getIdOf<FBOProperty>();
//}

#endif // FBOPROPERTY_H
