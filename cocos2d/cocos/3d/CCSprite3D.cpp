//
//  SkyboxNode.m
//  testar1
//
//  Created by Pasi Kettunen on 12.12.2012.
//
//

#include "CCSprite3D.h"
#include "CCMesh.h"
#include "CCTexture2D.h"
#include "CCGLProgram.h"
#include "CCDirector.h"
#include "CCTextureCache.h"
#include "renderer/CCRenderer.h"

#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

#define USE_VBO

#define STRINGIFY(A)  #A
//#include "../Shaders/TexturedLighting.es2.vert.h"
#include "TexturedLighting1.es2.vert.h"
#include "TexturedLighting.es2.frag.h"
#include "ColorLighting1.es2.frag.h"

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
UniformHandles m_uniforms;
AttributeHandles m_attributes;

Sprite3D* Sprite3D::create(const std::string &modelPath, const std::string &texturePath)
{
    auto ret = new Sprite3D;
    if( ret && ret->init(modelPath, texturePath)) {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}

Sprite3D::Sprite3D()
: _texture(nullptr)
{
}

Sprite3D::~Sprite3D()
{
}

bool Sprite3D::init(const std::string &modelPath, const std::string &texturePath)
{
    auto model = new Mesh(modelPath);
    if( texturePath.size()) {
        setTextureName(texturePath);
    }
    setModel(model);
    
    return true;
}

void Sprite3D::initializeModel()
{
    if (_model) {

        _model->generateVertices(_vertices, 0);
        
        //int indexCount = _model->getTriangleIndexCount();
        //_indices.resize(indexCount);
        _model->generateTriangleIndices(_indices);
        _drawable.IndexCount = _indices.size();

        delete _model;
        _model = NULL;
#ifdef USE_VBO
        this->buildBuffers();
#endif
        this->updateBlendFunc();
        buildProgram( _texture->getName() != 0);
    }
}

void Sprite3D::setModel(Mesh *model)
{
    _model = model;
    this->initializeModel();
}

bool Sprite3D::buildProgram(bool textured)
{
    auto shaderProgram = new GLProgram();

    // Create the GLSL program.
    if (textured) {
        shaderProgram->initWithByteArrays(SimpleVertexShader1, SimpleFragmentShader);
    }
    else
        shaderProgram->initWithByteArrays(SimpleVertexShader1, ColorLighting1);

    //glUseProgram(_program);

    shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

    shaderProgram->link();
    shaderProgram->updateUniforms();

    // Extract the handles to attributes and uniforms.
    m_attributes.Position = shaderProgram->getAttribLocation("Position");
    m_attributes.Normal = shaderProgram->getAttribLocation("Normal");
    
    m_uniforms.DiffuseMaterial = shaderProgram->getUniformLocation("DiffuseMaterial");
    if (textured) {
        m_attributes.TextureCoord = shaderProgram->getAttribLocation("TextureCoord");
        m_uniforms.Sampler = shaderProgram->getUniformLocation("Sampler");
    }
    else {
        m_attributes.TextureCoord = 0;
        m_uniforms.Sampler = 0;
    }
//    m_uniforms.Projection = shaderProgram->getUniformLocation("Projection");
//    m_uniforms.Modelview = shaderProgram->getUniformLocation("Modelview");
    m_uniforms.NormalMatrix = shaderProgram->getUniformLocation("NormalMatrix");
    m_uniforms.LightPosition = shaderProgram->getUniformLocation("LightPosition");
    m_uniforms.AmbientMaterial = shaderProgram->getUniformLocation("AmbientMaterial");
    m_uniforms.SpecularMaterial = shaderProgram->getUniformLocation("SpecularMaterial");
    m_uniforms.Shininess = shaderProgram->getUniformLocation("Shininess");

    setShaderProgram(shaderProgram);

    return true;
}

#ifdef USE_VBO
void Sprite3D::buildBuffers()
{
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 _vertices.size() * sizeof(_vertices[0]),
                 &_vertices[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Create a new VBO for the indices
    ssize_t indexCount = _indices.size();// model->GetTriangleIndexCount();
    GLuint indexBuffer;

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexCount * sizeof(GLushort),
                 &_indices[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    _drawable.VertexBuffer = vertexBuffer;
    _drawable.IndexBuffer = indexBuffer;
    _drawable.IndexCount = indexCount;
}

#endif
void Sprite3D::draw()
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Sprite3D::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void Sprite3D::onDraw()
{
    float _contentScale = _scaleX;

    //CC_NODE_DRAW_SETUP();
    //glDisable(GL_CULL_FACE);
    glEnable(GL_CULL_FACE);
    
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins(_modelViewTransform);

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );
    kmGLLoadIdentity();
    
	if (_texture->getName()) {
        GL::bindTexture2D(_texture->getName());
        glUniform1i(m_uniforms.Sampler, 0);
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    }
    else {
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
    }
    
    // Set up some default material parameters.
    glUniform3f(m_uniforms.AmbientMaterial, 0.1f, 0.1f, 0.1f);
    glUniform3f(m_uniforms.SpecularMaterial, 0.5, 0.5, 0.5);
    glUniform1f(m_uniforms.Shininess, 10);
    //glUniform1f(m_uniforms.Shininess, 0);
    
    // Set the diffuse color.
    vec3 color = vec3(1,1, 1.1) * .50;
    glUniform3f(m_uniforms.DiffuseMaterial, color.x, color.y, color.z);
    //glVertexAttrib3f(m_attributes.DiffuseMaterial, color.x, color.y, color.z);
    
    // Initialize various state.
    glEnableVertexAttribArray(m_attributes.Position);
    glEnableVertexAttribArray(m_attributes.Normal);
    if (_texture->getName())
        glEnableVertexAttribArray(m_attributes.TextureCoord);
    glEnable(GL_DEPTH_TEST);

    // Set the light position.
    vec3 lightPosition = vec3(-2.25, 0.25, 1);
    lightPosition.Normalize();
    vec4 lp = vec4(lightPosition.x, lightPosition.y, lightPosition.z, 0);
    glUniform3fv(m_uniforms.LightPosition, 1, lp.Pointer());

    // Set the normal matrix.
    // It's orthogonal, so its Inverse-Transpose is itself!
    kmMat3 normals;
    kmMat3AssignMat4(&normals, &_modelViewTransform);
    glUniformMatrix3fv(m_uniforms.NormalMatrix, 1, 0, &normals.mat[0]);

    // Draw the surface using VBOs
    int stride = sizeof(vec3) + sizeof(vec3) + sizeof(vec2);
    const GLvoid* normalOffset = (const GLvoid*) sizeof(vec3);
    const GLvoid* texCoordOffset = (const GLvoid*) (2 * sizeof(vec3));
    GLint position = m_attributes.Position;
    GLint normal = m_attributes.Normal;
    GLint texCoord = m_attributes.TextureCoord;

    glBindBuffer(GL_ARRAY_BUFFER, _drawable.VertexBuffer);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, stride, normalOffset);
    if (_texture->getName())
        glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, stride, texCoordOffset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _drawable.IndexBuffer);
    glDrawElements(GL_TRIANGLES, _drawable.IndexCount, GL_UNSIGNED_SHORT, 0);
    
    //glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    
    /*glDisableVertexAttribArray(m_attributes.Position);
    glDisableVertexAttribArray(m_attributes.Normal);
    if ([texture_ name])
        glDisableVertexAttribArray(m_attributes.TextureCoord);*/

    glDisable(GL_DEPTH_TEST);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _drawable.IndexCount);
    //glEnable(GL_CULL_FACE);
}

void Sprite3D::setTextureName(const std::string& textureName)
{
    auto cache = Director::getInstance()->getTextureCache();
    Texture2D *tex = cache->addImage(textureName);
	if( tex ) {
        this->setTexture(tex);
    }
}

void Sprite3D::removeTexture()
{
	if( _texture ) {
        _texture->release();

        this->updateBlendFunc();
        buildProgram(_texture->getName() != 0);
	}
}

#pragma mark Sprite3D - CocosNodeTexture protocol

void Sprite3D::updateBlendFunc()
{
	// it is possible to have an untextured sprite
	if( !_texture || ! _texture->hasPremultipliedAlpha() ) {
		_blendFunc.src = GL_SRC_ALPHA;
		_blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	} else {
		_blendFunc.src = CC_BLEND_SRC;
		_blendFunc.dst = CC_BLEND_DST;
	}
}

void Sprite3D::setTexture(Texture2D* texture)
{
	CCASSERT( texture , "setTexture expects a Texture2D. Invalid argument");
    
	if( _texture != texture ) {
        if(_texture)
            _texture->release();

		_texture = texture;
        _texture->retain();
        
        this->updateBlendFunc();
        buildProgram( _texture->getName() != 0);
	}
}

NS_CC_END
