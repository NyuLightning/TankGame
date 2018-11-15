/*
 *  camera.h
 *  robot
 *
 *  Created by bdr on 13.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#ifndef CAMERA_H
#define CAMERA_H
#include "sgobject.h"
#include "physics.h"
#include "structure.h"

//! Realisierung einer einfachen  virtuellen Kamera. Dies ist die Basisklasse und stellt die Projektions- und Modelview-Matrix
//! sowie sinnvolle Methoden für die Manipulation zur Verfügung.
//! Diese Klasse ist einfach gehalten, erlaubt die Rotation um alle Hauptachsen. Daher ist hier aber auch ein Gimbal
//! Lock möglich.
//! Subklassen (z.B. ControllableCamera) können andere Strategien für verschiedene Methoden zur Verfügung stellen.
class Camera

{
public:
    Camera();
    virtual ~Camera() {}

    //! Auslesen der Position des Eyes
    const QVector3D& getPosition() const;

    //! Festlegen des Eyes
    void setPosition(float x, float y, float z){setPosition(QVector3D(x, y, z));}

    //! Festlegen des Eyes
    void setPosition(const QVector3D& position);

    //! Verschieben des Eyes in pos. Z-Richtung
    void incZPos();

    //! Verschieben des Eyes in pos. X-Richtung
    void incXPos();

    //! Verschieben des Eyes in pos. Y-Richtung
    void incYPos();

    //! Verschieben des Eyes in neg. Z-Richtung
    void decZPos();

    //! Verschieben des Eyes in neg. X-Richtung
    void decXPos();

    //! Verschieben des Eyes in neg. Y-Richtung
    void decYPos();

    //! Blick nach oben/unten, verändert nicht die Bewegungsrichtung
    void incCamAlphaX();

    //! Blick nach oben/unten, verändert nicht die Bewegungsrichtung
    void decCamAlphaX();

    //! Drehung um X-Achse (-> also oben/unten)
    void incAlphaX();

    //! Drehung um X-Achse (-> also oben/unten)
    void decAlphaX();

    //! Drehung um Y-Achse (-> also links/rechts)
    void incBetaY();

    //! Drehung um Y-Achse (-> also links/rechts)
    void decBetaY();

    //! Drehung um Z-Achse (also roll)
    void incGammaZ();

    //! Drehung um Z-Achse (also roll)
    void decGammaZ();

    //! Bewegung in KKS-Blickrichtung
    void incViewDirection();

    //! Bewegung in negative KKS-Blickrichtung
    void decViewDirection();

    //! Bewegung nach rechts
    void incStrave();

    //! Bewegung nach links
    void decStrave();

    //! Festlegen von Near Clipping - n gibt Abstand zur Kamera an.
    void setNear(float n);

    //! Festlegen von Far Clipping - f gibt Abstand zur Kamera an
    void setFar(float f);

    //! Öffentliche Methode, die benutzt werden kann, um z.B. Skalierungen auszurechnen
    float getDepth(){return (mCamData.farPlane - mCamData.nearPlane);}

    //! Öffnungswinkel festlegen
    void setAperture(float a);

    //! Augenposition setzen
    void setEyePosition(QVector3D eyePosition);

    //! Abstand Augenposition setzen
    void setDeltaEyePosition(QVector3D deltaEyePosition);

    //! Rückgabe der aktuellen Kamerawerte
    CamData getCamData();

    //! Setzen von Kamerawerten
    void setCamData(CamData pCamData);

    //! Setzen der Achsen des CCS
    void setCCSAxes(QVector3D pCCSX, QVector3D pCCSY, QVector3D pCCSZ);

    float getRotSpeed() const;

    //! Setzen der Rotationsgeschwindigkeit
    void setRotSpeed(float rotSpeed);

    float getLocSpeed() const;

    //! Setzen der Bewegungsgeschwindigkeit
    void setLocSpeed(float locSpeed);

    //! Bewegen im Weltkoordinatensystem
    void moveWCS(float pDX, float pDY, float pDZ);

    //! Bewegen im Kamerakoordinatensystem
    void moveCCS(float pDX, float pDY, float pDZ);

    //! Rotieren über Rotationswinkel yaw (y-Achse), pitch (x-Achse), roll (z-Achse)
    void rotate(float pYaw, float pPitch, float pRoll);

    //! Setzt Kamerakoordinatensystem zurück
    void resetCCS();

    //! Up-Vector zurückgeben
    QVector3D  getUp();
    //! Viewdirection zurückgeben
    QVector3D getDir();

    //! Nach Berechnung der Matrizen auf false setzen
    void noMatrixCalculationNeeded();

private:

    CamData mCamData;

protected:

    float mRotSpeed;
    float mLocSpeed;

    static const QVector3D cWCS_X, cWCS_Y, cWCS_Z; // Weltkoordinatenachsen

    void orthogonalizeAxes();
};

#endif // CAMERA_H
