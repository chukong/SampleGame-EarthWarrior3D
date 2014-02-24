
#ifndef __CCMESH_H_
#define __CCMESH_H_

#include <string>
#include <vector>

#include "CCGL.h"
#include "CCPlatformMacros.h"
#include "Vector.h"

NS_CC_BEGIN

struct Face
{
    ivec3 face;
    ivec3 texi;
};

class Mesh
{
public:
    Mesh(const std::string& name);
    ~Mesh();

    int getVertexCount(/*int &texInCount*/) const;
    int getTexelCount() const;
    
    int getLineIndexCount() const { return 0; }
    int getTriangleIndexCount() const;
    void generateVertices(std::vector<float>& vertices, unsigned char flags) const;
    void generateLineIndices(std::vector<unsigned short>& indices) const {}
    void generateTriangleIndices(std::vector<unsigned short>& indices) const;
    //void readTexels(std::vector<vec2>& ) const;

protected:
    void countVertexData() const;
    std::string _name;
    //vector<ivec3> m_faces;
    std::vector<Face> _faces;
    std::vector<vec2> _texels;
    mutable int _faceCount;
    mutable int _vertexCount;
    mutable int _texelCount;
    
    static const int MAX_LINE_SIZE = 128;
};

NS_CC_END

#endif // __CCMESH_H_