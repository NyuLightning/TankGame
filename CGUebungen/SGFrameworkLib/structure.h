#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include <QVector3D>
#include <QString>

//! Diese Klasse generiert zwei Datenstrukturen um eine kompaktere
//! Übergabe von Parametern zu gewährleisten

struct CamData
{
        float nearPlane;
        float farPlane;
        float aperture;
        float camAlphaX;
        float rotSpeed;
        float locSpeed;
        bool rotLocChanged;
        bool frustumChanged;
        bool lockZRotation;
        QVector3D eyePosition;
        QVector3D deltaEyePosition;
        QVector3D cameraPosition;
        QVector3D CCS_X;
        QVector3D CCS_Y;
        QVector3D CCS_Z;
};

struct CanvasData
{
        QString id;
        QString leftCanvasId;
        QVector3D leftBottom;
        QVector3D rightBottom;
        QVector3D leftTop;
        float width;
        float height;
        float angle;
        bool hasCoordinates;
};

#endif // STRUCTURE_H
