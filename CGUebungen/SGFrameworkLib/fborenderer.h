#ifndef FBORENDERER_H
#define FBORENDERER_H
#include "renderconfiguration.h"
#include "renderer.h"

class Drawable;

//! FBORenderer implementiert ein Offscreen-Rendering in ein FBO. Das FBO kann dann z.B. über eine FBOProperty an ein
//! Drawable "gehängt" werden. Es ist ein PreRenderer, der also vor dem eigentlichen Rendering durchlaufen wird.
class FBORenderer : public RenderConfiguration, public Renderer
{
public:
    //! Erzeugt einen neuen FBORenderer. Über \param sortDrawables kann zwischen einem SortedRenderingSGObjectVisitor
    //! und einem PreOrderRenderingSGObjectVisitor Besucher gewechselt werden. Die Verwendung von Sortiertem Rendering
    //! wird empfolen da diese mehr Fps liefert. PreOrder Rendering wird hauptsächlich unterstützt um herauszufinden ob
    //! ein Problem durch das sortierte Rendern entsteht und Performanz Vergleiche zwischen den beiden Rendering
    //! Methoden zu erstellen.
    FBORenderer(bool sortDrawables = true);

    //! Destruktor löscht FBO + Textur + Renderbuffer
    virtual ~FBORenderer();

    //! \param renderTree ist der in das FBO zu rendernde teilbaum. \param fboOwnerDrawable ist das Drawable auf das die
    //! FBO texture anschließend gemapt/gerendert wird, dies wird benötigt das es beim rendern in das FBO deaktiviert
    //! werden muss, da es ansonsten das Bild verdecken würde.
    virtual void init(Node* renderTree, float boxSize, int texDim, Drawable* fboOwnerDrawable);

    //! Rendert die Szene in das FBO
    virtual void renderScene() override;

    //! aktualisiert die Projektions Matrix der Camera. Überschreibt RenderConfiguration::update(), da die view matrix nicht
    //! berechnet wird. Dies geschieht bereits in renderScene()
    virtual void update(CamData data) override; // Methode aus RenderConfiguration überschreiben

    //! Getter für die Id der Textur in die das FBO rendert.
    virtual GLuint getTexID() {return (mRenderDest);}

    //! Wird aufgerufen wenn das fenster Vergrösert/Verkleinert wird.
    virtual void reshape(int /*w*/, int /*h*/) override {}

    //! Setzen der Auflösung - muss vor init gerufen werden!
    virtual void setRes(int pRes) {mFboHeight = mFboWidth = pRes;}

private:
    GLuint mFBO;          //!< Handle auf FBO
    GLuint mRenderbuffer; //!< Handle zu Renderbuffer (Speicher), der an das FBO gebunden wird
    GLuint mRenderDest;   //!< Handle der Textur, in die gerendert wird.
    GLuint mTexDim;       //!< Dimension der Textur, in die gerendert wird.
    bool mValid;          //!< gibt an ob das FBO korrekt erstellt und gebunden werden konnte

    GLsizei mFboWidth; //!< Die horizontale auflösung des FBOs
    GLsizei mFboHeight; //!< Die vertikale auflösung des FBOs

    //! Das Drawable auf das das FBO gerendert werden soll. Dies muss werend des renderns der FBO texturen deaktiviert
    //! werden da es sonst das bild überdecken würde!
    Drawable* mFboOwnerDrawable;

    //! Überprüft ob das Framebuffer-Object richtig erstellt und gebunden wurde.
    bool checkFramebufferStatus();
};

//inline GLuint FBORenderer::getTexID()
//{
//    return (mRenderDest);
//}

//inline void FBORenderer::reshape(int /*w*/, int /*h*/)
//{
//}

#endif // FBORENDERER_H
