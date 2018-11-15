#ifndef RENDERCONFIGURATION_H
#define RENDERCONFIGURATION_H
#include "structure.h"
#include "canvas.h"
#include "viewport.h"
#include "reshapelistener.h"


//! Diese Klasse berechnet die Positionierung
//! und Konfiguration (stereo...) der Ziele für das Rendering
//! Das können Displays im Raum sein. Oder im Prerendering Texturen (FBOs).
//! Dazu beinhält die Klasse die Viewports, sowie zu den einzelnen
//! Viewports die Projektions- und Viewmatrizen



class RenderConfiguration : public ReshapeListener
{
public:
    RenderConfiguration(bool pDefaultConfig=false, QString pPath=QString());

    //! Setzen des Pfades in dem das XML-File sich befindet
    void setPath(const QString path = "../SGFrameworkLib/cave.xml", const QString caveID = "");

    //!Setzt die gelesen Daten aus dem XML-File
    void setParserData(QVector<CanvasData> canvas);

    CanvasData getOldCanvas() const;

    void setOldCanvas(const CanvasData &oldCanvas);

    //!Berechnung und Rückgabe der ViewMatrix
    QMatrix4x4 getViewMatrix();

    //!Rückgabe der Projektionsmatrix für den aktuellen Viewport
    QMatrix4x4 getProjectionMatrix();

    //!Geht alle Viewports durch
    bool nextViewport();

    //!Setzen des Viewports
    virtual void setViewport();

    //!Updaten der Projektions- und Viewmatrix
    virtual void update(CamData data);

    //! 3D-Rendering setzen
    void setStereo(const bool stereo = true);

    //! Änderung der Größe des Ausgabefensters
    virtual void reshape(int w, int h);

protected:

    //!Fügt alle Leinwände/Monitore hinzu
    void addCanvas(QVector <CanvasData> canvasList);

    //!Berechnet automatisch die benachbarten Leinwände, wenn vorhanden
    void calculateCorners(QVector <CanvasData> canvasList);

    //!Setzt die Anzahl der benötigten Viewports
    void calculateviewportSizeFromCanvasCount();

    Canvas mCanvas;
    CanvasData mOldCanvas;
    QVector <CanvasData> mCanvasData;

    //! Hält alle Viewports
    QVector<Viewport> mViewport;

    //! Aktueller Viewport
    unsigned short mCurrentViewport;

    //! Nötig für 3D bei derUnterscheidung ob untere oder oberer Viewport gesetzt wird
    unsigned short mPos;

    //! Angabe ob 3D gerendert werden soll
    bool mStereo;

    //! Verhindert unnötige Neuberechnung des Viewports wenn keine Änderungen erfolgt sind
    bool mWindowChanged;

    QVector<QMatrix4x4> mProjectionsMatrix;
    QMatrix4x4 mViewMatrix;
};

#endif // RENDERCONFIGURATION_H
