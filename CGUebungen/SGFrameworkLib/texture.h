/*
 *  texture.h
 *  heightmap_textured
 *
 *  Created by bdr on 27.03.09.
 *  Copyright 2009 Hochschule Kempten. All rights reserved.
 *
 */

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "opengl.h"
#include "drawableproperty.h"
#include <QImage>

//! Klasse zum Rendering von 2D-Texturen
class Texture : public DrawableProperty
{
public:
    Texture(int unit = 0) {initMembers();mTextureUnit = unit;}
    Texture(const QString& pfad, int unit = 0) {initMembers();mTextureUnit = unit;this->loadPicture(pfad);}

    //! Bild aus Datei laden
    void loadPicture(QString pfad);

    //! Rendering der Textur anschalten \see DrawableProperty::turnOff()
    virtual void turnOff(Shader* shader) override;

    //! Rendering der Textur ausschalten \see DrawableProperty::turnOn()
    virtual void turnOn(Shader* shader) override;
    void setUnit(int unit) {mTextureUnit = unit;}
    void setDimMode(int mode);
    void setMaxFilter(int mode) {mMaxFilter = mode;}
    void setMinFilter(int mode) {mMinFilter = mode;}
    void setWrapMode(int mode) {mWrapMode = mode;}
    void setAnisotropyLevel(unsigned int level) {mAnisotropyLevel = std::max((int)std::min((unsigned int)mMaximumAnisotropy, level), 1);}
    virtual void makeStripes(int size, int thickness, bool buildmipmaps = true);
    void makeDummy();
    virtual ~Texture();
    void setForceInitialize(bool pForceInitialize) {mForceInitialize = pForceInitialize;}

    //! \see DrawableProperty::getId()
    static DrawablePropertyId getPropertyId() {return DrawablePropertyIdGeter::getIdOf<Texture>();}

    //! \see DrawableProperty::getId()
    virtual DrawablePropertyId getId() const override;

    //! Gibt true zur?ck wenn das geladene Bild einen Alpha-Kanal besitzt
    bool hasAlphaChannel() const;

protected:
    //! Textur initialisieren und laden - im Fehlerfall Dummy erzeugen
    virtual void textureInit(bool buildmipmaps = true);

    //! Maps bauen und in OpenGL laden
    virtual void buildMaps(bool buildmipmaps = true);

    //! Dummy Textur erzeugen
    void initMembers();

    GLuint mTexName;
    int mTexDim;
    int mTextureUnit;
    int mMinFilter;
    int mMaxFilter;
    int mWrapMode;
    float mMaximumAnisotropy;
    unsigned int mAnisotropyLevel;
    bool mInitialized;
    bool mForceInitialize;
    QImage* mImage;     // Benutzt bei TEXTURE_2D
    QImage* mImages[6]; // Benutzt fuer CubeTexture
};

//inline Texture::Texture(int unit)
//{
//    initMembers();
//    mTextureUnit = unit;
//}

//inline Texture::Texture(const QString& pfad, int unit)
//{
//    initMembers();
//    mTextureUnit = unit;
//    this->loadPicture(pfad);
//}

//inline void Texture::setUnit(int unit)
//{
//    mTextureUnit = unit;
//}

//inline void Texture::setMaxFilter(int mode)
//{
//    mMaxFilter = mode;
//}

//inline void Texture::setMinFilter(int mode)
//{
//    mMinFilter = mode;
//}

//inline void Texture::setWrapMode(int mode)
//{
//    mWrapMode = mode;
//}

//inline void Texture::setAnisotropyLevel(unsigned int level)
//{
//    mAnisotropyLevel = std::max((int)std::min((unsigned int)mMaximumAnisotropy, level), 1);
//}

//inline DrawablePropertyId Texture::getPropertyId()
//{
//    return DrawablePropertyIdGeter::getIdOf<Texture>();
//}

#endif
