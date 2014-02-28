
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

struct FaceVertex
{
    FaceVertex(int vIndex, int uvIndex, int normIndex)
    : _vIndex(vIndex)
    , _uvIndex(uvIndex)
    , _normIndex(normIndex)
    {
    }
    int _vIndex;
    int _uvIndex;
    int _normIndex;
};

struct RenderMesh
{
    struct RenderVertex
    {
        vec3 vertex;
        vec3 normal;
        vec2 uv;
    };
    
    std::vector<RenderVertex> _vertexs;
    std::vector<unsigned short> _indices;
};

struct ObjMeshData
{
    //mesh data
    std::vector<vec3> _vertexLists;
    std::vector<vec2> _uvVertexLists;
    std::vector<vec3> _normalVertexLists;
    std::vector<std::vector<FaceVertex>> _faceLists;
    
public:
    bool checkBound() const;
    bool isTriangeMesh() const;
    void triangular();
    void trianglarAndGenerateNormals();
    void convertToRenderMesh(RenderMesh& renderMesh);
};

class Mesh
{
public:
    Mesh(const std::string& name);
    ~Mesh();
    
    bool loadFromFile(const std::string& name);
    void generateVertices(std::vector<float>& vertices, unsigned char flags) const;
    void generateTriangleIndices(std::vector<unsigned short>& indices) const;
    //void readTexels(std::vector<vec2>& ) const;

protected:
    void generateLineIndices(std::vector<unsigned short>& indices) const {}
    int getVertexCount(/*int &texInCount*/) const;
    int getTexelCount() const;
    
    int getLineIndexCount() const { return 0; }
    int getTriangleIndexCount() const;

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
private:
    RenderMesh _renderableMesh;
    
};

NS_CC_END

#endif // __CCMESH_H_