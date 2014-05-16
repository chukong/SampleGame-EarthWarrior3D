//
//  Sprite3DEffect.h
//  Moon3d
//
//  Created by Huabing.Xu on 5/15/14.
//
//

#ifndef __Moon3d__Sprite3DEffect__
#define __Moon3d__Sprite3DEffect__

#include <iostream>

#include "cocos2d.h"

USING_NS_CC;

class EffectSprite3D;

class Effect3D : public Ref
{
public:
    virtual void drawWithSprite(EffectSprite3D* sprite, const Mat4 &transform) = 0;
protected:
    Effect3D() : _glProgramState(nullptr) {}
    virtual ~Effect3D()
    {
        CC_SAFE_RELEASE(_glProgramState);
    }
protected:
    GLProgramState* _glProgramState;
};

class Effect3DOutline: public Effect3D
{
public:
    static Effect3DOutline* create();
    
    void setOutlineColor(const Vec3& color);
    
    void setOutlineWidth(float width);
    
    void drawWithSprite(EffectSprite3D* sprite, const Mat4 &transform);
    
protected:
    
    Effect3DOutline();
    virtual ~Effect3DOutline();
    
    bool init();
    
    Vec3 _outlineColor;
    float _outlineWidth;
public:
    static const std::string _vertShaderFile;
    static const std::string _fragShaderFile;
    static const std::string _keyInGLProgramCache;
    static GLProgram* getOrCreateProgram();
    
};

class EffectSprite3D : public Sprite3D
{
public:
    static EffectSprite3D* createFromObjFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
    void setEffect3D(Effect3D* effect);
    void addEffect(Effect3D* effect, ssize_t order);
    void eraseEffect(Effect3D* effect);
    ssize_t getEffectCount() const;
    Effect3D* getEffect(ssize_t index) const;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
protected:
    EffectSprite3D();
    virtual ~EffectSprite3D();
    
    std::vector<std::tuple<ssize_t,Effect3D*,CustomCommand>> _effects;
    Effect3D* _defaultEffect;
    CustomCommand _command;
};

#endif /* defined(__Moon3d__Sprite3DEffect__) */
