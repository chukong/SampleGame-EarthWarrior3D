#include "CCMesh.h"

#include <list>
#include <fstream>
#include <iostream>

#include "CCGL.h"
#include "ccMacros.h"
#include "CCFileUtils.h"

using namespace std;

NS_CC_BEGIN

Mesh::Mesh(const string& name)
: _faceCount(0)
, _vertexCount(0)
, _texelCount(0)
{
    _name = FileUtils::getInstance()->fullPathForFilename(name);

    if (getTexelCount() > 0) {
        _texels.resize(getTexelCount());
    }
    auto texel = _texels.begin();

    _faces.resize(getTriangleIndexCount() / 3);
    ifstream objFile(_name.c_str());
    float dumy;
    vector<Face>::iterator face = _faces.begin();
    while (objFile) {
        char c = objFile.get();
        if (c == 'f' && objFile.get() == ' ') {
            CCASSERT(face != _faces.end(), "parse error");
            face->texi = ivec3(1,1,1);
            objFile >> face->face.x;
            if ((c = objFile.get()) == '/') {
                objFile >> face->texi.x;
                if ((c = objFile.get()) == '/')
                    objFile >> dumy;
            }
            
            objFile >> face->face.y;
            if ((c = objFile.get()) == '/') {
                objFile >> face->texi.y;
                if ((c = objFile.get()) == '/')
                    objFile >> dumy;
            }
            
            objFile >> face->face.z;
            if ((c = objFile.get()) == '/') {
                objFile >> face->texi.z;
                if ((c = objFile.get()) == '/') {
                    objFile >> dumy;
                }
            }
            if (c != '\n')
                objFile.ignore(MAX_LINE_SIZE, '\n');
            
            face->face -= ivec3(1, 1, 1);
            face->texi -= ivec3(1, 1, 1);
            ++face;
        }
        else if (c == 'v') {
            if ((c = objFile.get()) == 't') {
                objFile >> texel->x >> texel->y;

                /*while (texel->x >= 1.000) {
                    texel->x -= 1.0;
                }
                while (texel->y >= 1.000) {
                    texel->y -= 1.0;
                }*/
//                texel->x = 1.0 - texel->x;
                //if (texel->x > 1.0 || texel->y > 1.0) {
                texel->y = 1.0 - texel->y;
                ++texel;
                //}
            }
            if (c != '\n')
                objFile.ignore(MAX_LINE_SIZE, '\n');
        }
        else if (c != '\n')
            objFile.ignore(MAX_LINE_SIZE, '\n');
    }
    CCASSERT(face == _faces.end(), "parse error");
}

Mesh::~Mesh()
{
}

void Mesh::countVertexData() const
{
    ifstream objFile(_name.c_str());
    _faceCount = 0;
    while (objFile) {
        char c = objFile.get();
        if (c == 'v') {
            if ((c = objFile.get()) == ' ')
                _vertexCount++;
            else if (c == 't')
                _texelCount++;
        }
        else if (c == 'f') {
            if ((c = objFile.get()) == ' ')
                _faceCount++;
        }
        objFile.ignore(MAX_LINE_SIZE, '\n');
    }
}

int Mesh::getVertexCount() const
{
    if (_vertexCount != 0) {
        return _vertexCount;
    }
    countVertexData();
    
    return _vertexCount;
}

int Mesh::getTexelCount() const {
    if (_vertexCount != 0) {
        return _texelCount;
    }
    countVertexData();
    
    return _texelCount;
}
int Mesh::getTriangleIndexCount() const
{
    if (_faceCount != 0)
        return _faceCount * 3;
    countVertexData();

    return _faceCount * 3;
}

void Mesh::generateVertices(vector<float>& floats, unsigned char flags) const
{
    //assert(flags == VertexFlagsNormals && "Unsupported flags.");

    struct Vertex {
        vec3 Position;
        vec3 Normal;
        vec2 Texel;
    };

    // Read in the vertex positions and initialize lighting normals to (0, 0, 0).
    int texelCount = getTexelCount();
    floats.resize(getVertexCount() * 8);// 6);
    ifstream objFile(_name.c_str());
    Vertex* vertex = (Vertex*) &floats[0];
    while (objFile) {
        char c = objFile.get();
        if (c == 'v' && objFile.get() == ' ') {
            vertex->Normal = vec3(0, 0, 0);
            vec3& position = (vertex)->Position;
            objFile >> position.x >> position.y >> position.z;
            vec2& texel = (vertex)->Texel;
            texel.x = position.x * .5 + .5;
            texel.y = position.y * -.5 + .5;
            vertex++;
        }
        objFile.ignore(MAX_LINE_SIZE, '\n');
    }

    vertex = (Vertex*) &floats[0];
    for (ssize_t faceIndex = 0; faceIndex < _faces.size(); ++faceIndex) {
        ivec3 face = _faces[faceIndex].face;
        //Face face = _faces[faceIndex];

        // Compute the facet normal.
        vec3 a = vertex[face.x].Position;
        vec3 b = vertex[face.y].Position;
        vec3 c = vertex[face.z].Position;
        vec3 facetNormal = (b - a).Cross(c - a);

        // Add the facet normal to the lighting normal of each adjoining vertex.
        vertex[face.x].Normal += facetNormal;
        vertex[face.y].Normal += facetNormal;
        vertex[face.z].Normal += facetNormal;
        
        if (texelCount) {
            ivec3 texi = _faces[faceIndex].texi;
            vertex[face.x].Texel = _texels[texi.x];
            vertex[face.y].Texel = _texels[texi.y];
            vertex[face.z].Texel = _texels[texi.z];
        }
    }

    // Normalize the normals.
    for (int v = 0; v < getVertexCount(); ++v)
        vertex[v].Normal.Normalize();
}

void Mesh::generateTriangleIndices(vector<unsigned short>& indices) const
{
    indices.resize(getTriangleIndexCount());
    vector<unsigned short>::iterator index = indices.begin();
    for (vector<Face>::const_iterator f = _faces.begin(); f != _faces.end(); ++f) {
        *index++ = f->face.x;
        *index++ = f->face.y;
        *index++ = f->face.z;
    }
}

NS_CC_END
