//
//  SkyboxNode.h
//  testar1
//
//  Created by Pasi Kettunen on 12.12.2012.
//
//


/*
 *
 * SkyboxNode is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SkyboxNode is distributed WITHOUT ANY WARRANTY; See the
 * GNU General Public License for more details.
 *
 * Note: The 'cocos2d for iPhone' license also applies if used in conjunction
 * with the Cocos2D framework.
 */

#ifndef __SPRITE3D_H_
#define __SPRITE3D_H_

#include <vector>

#include "cocos2d.h"

#include "Mesh.h"

struct Drawable {
    GLuint VertexBuffer;
    GLuint IndexBuffer;
    ssize_t IndexCount;
};

struct UniformHandles
{
    GLuint NormalMatrix;
    GLuint LightPosition;
    GLint AmbientMaterial;
    GLint SpecularMaterial;
    GLint DiffuseMaterial;
    GLint Shininess;
    GLint Sampler;
};

struct AttributeHandles
{
    GLint Position;
    GLint Normal;
    GLint TextureCoord;
};

class Sprite3D : public cocos2d::Node
{
public:
    static Sprite3D* create(const std::string &modelPath, const std::string &texturePath="");
    void setOutline(float width, cocos2d::Color3B color);

protected:
    Sprite3D();
    virtual ~Sprite3D();
    bool init(const std::string &modelPath, const std::string &texturePath);

    void initializeModel();
    void setModel(Mesh *model);
    bool buildProgram(bool textured);
    void buildBuffers();
    void draw(cocos2d::Renderer* renderer, const kmMat4 &transform, bool transformUpdated);
    void onDraw(const kmMat4 &transform, bool transformUpdated);
    void setTexture(cocos2d::Texture2D* texture);
    void updateBlendFunc();
    void setTextureName(const std::string& textureName);
    void removeTexture();

    // the current rotation offset
    //float xRot, yRot, zRot;
    Mesh *_model;
    
    Drawable _drawable;
    
    std::vector<GLfloat> _vertices;
    std::vector<GLushort> _indices;

    cocos2d::BlendFunc _blendFunc;
    cocos2d::Texture2D *_texture;
    cocos2d::CustomCommand _customCommand;
    
    bool _outLine = false;
    float _outLineWidth;
    cocos2d::Color3B _outlineColor;
    cocos2d::GLProgram *_outlineShader;

    UniformHandles _uniforms;
    UniformHandles _uniformsOutline;
    AttributeHandles _attributes;
    AttributeHandles _attributesOutline;
};

#endif // __SPRITE3D_H_
