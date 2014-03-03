#include "CCMesh.h"

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "CCGL.h"
#include "ccMacros.h"
#include "CCFileUtils.h"


using namespace std;

NS_CC_BEGIN

class ObjMeshParser
{
public:
    void parse(std::istream& streamIn, ObjMeshData& meshData);
protected:
    bool parseComment(std::istream& lineStream, ObjMeshData& meshData);
    bool parseVertex(std::istream& lineStream, ObjMeshData& meshData);
    bool parseTextureVertex(std::istream& lineStream, ObjMeshData& meshData);
    bool parseNormal(std::istream& lineStream, ObjMeshData& meshData);
    bool parseFace(std::istream& lineStream, ObjMeshData& meshData);
    //void onLoadFace()
    void logParseError(int lineCount, const std::string& lineData);
};
void ObjMeshParser::logParseError(int lineCount, const std::string& lineData)
{
    CCLOG("Parse Obj file ERROR: line---%d, data---%s", lineCount, lineData.c_str());
}

bool ObjMeshParser::parseComment(std::istream& lineStream, ObjMeshData& meshData)
{
    return true;
    //std::string comment;
    //std::getline(lineStream,comment);
    //todo, log comment
}

bool ObjMeshParser::parseVertex(std::istream& lineStream, ObjMeshData& meshData)
{
    float x,y,z;
    char whiteSpacex_y,whiteSpacey_z;
    lineStream>>x>>whiteSpacex_y>>std::ws>>y>>whiteSpacey_z>>std::ws>>z>>std::ws;
    //check
    if(lineStream.bad() || !lineStream.eof() || !std::isspace(whiteSpacex_y) || !std::isspace(whiteSpacey_z))
    {
        return false;
    }

    meshData._vertexLists.push_back(vec3(x,y,z));
    return true;
}

bool ObjMeshParser::parseTextureVertex(std::istream& lineStream, ObjMeshData& meshData)
{
    float u,v;
    char whiteSpaceu_v;
    lineStream>>u>>whiteSpaceu_v>>std::ws>>v>>std::ws;
    //check
    if(lineStream.bad() || !lineStream.eof() || !std::isspace(whiteSpaceu_v))
    {
        return false;
    }
    v = 1 - v;
    meshData._uvVertexLists.push_back(vec2(u,v));
    return true;
}

bool ObjMeshParser::parseNormal(std::istream& lineStream, ObjMeshData& meshData)
{
    float x,y,z;
    char whiteSpacex_y,whiteSpacey_z;
    lineStream>>x>>whiteSpacex_y>>std::ws>>y>>whiteSpacey_z>>std::ws>>z>>std::ws;
    //check
    if(lineStream.bad() || !lineStream.eof() || !std::isspace(whiteSpacex_y) || !std::isspace(whiteSpacey_z))
    {
        return false;
    }
    
    meshData._normalVertexLists.push_back(vec3(x,y,z));
    return true;
}

bool ObjMeshParser::parseFace(std::istream& lineStream, ObjMeshData& meshData)
{
    std::vector<FaceVertex> face;
    
    while (!lineStream.bad() && !lineStream.eof())
    {
        std::string faceVertexString;
        lineStream >> faceVertexString;
        
        //parse face vertex;
        {
            FaceVertex v(-1,-1,-1);
            char placeHolder;
            std::stringstream faceVertexStream(faceVertexString);
            faceVertexStream >> v._vIndex;
            if(!faceVertexStream.eof())
            {
                faceVertexStream >> placeHolder>>std::ws;
                if(placeHolder != '/') return false;
                if(faceVertexStream.peek() == '/')
                {
                    faceVertexStream >> placeHolder;
                    faceVertexStream >> v._normIndex;
                }
                else
                {
                    faceVertexStream >> v._uvIndex;
                    if(!faceVertexStream.eof())
                    {
                        faceVertexStream >> placeHolder;
                        if( placeHolder != '/') return false;
                        faceVertexStream >> v._normIndex;
                    }
                }
            }
            if(v._uvIndex != -1) v._uvIndex -= 1;
            if(v._normIndex != -1) v._normIndex -= 1;
            if(v._vIndex != -1) v._vIndex -= 1;
            face.push_back(v);
        }
        
        //try read white space
        char whiteSpace;
        if(!lineStream.eof())
        {
            lineStream >> whiteSpace >> std::ws;
            if(!std::isspace(whiteSpace)) return false;
        }
        
    }
    
    if(face.size() < 3) return false;
    meshData._faceLists.push_back(face);
    return true;
}

void ObjMeshParser::parse(std::istream &streamIn, ObjMeshData &meshData)
{
    std::string line;
    int line_number = 0;
    while (!streamIn.eof() && std::getline(streamIn, line))
    {
        ++line_number;
        std::istringstream stringstream(line);
        stringstream.unsetf(std::ios_base::skipws);
        
        stringstream >> std::ws;
        
        if(!stringstream.eof())
        {
            if(stringstream.peek() == '#')
            {
                char commentKey;
                stringstream>>commentKey;
                if(!parseComment(stringstream, meshData))
                {
                    logParseError(line_number,line);
                }
            }
            else
            {
                std::string keyword;
                stringstream >> keyword;
                char whiteSpace;
                if(keyword == "v")
                {
                    stringstream>>whiteSpace>>std::ws;
                    //check and parse
                    if(!std::isspace(whiteSpace) || stringstream.bad() || !parseVertex(stringstream, meshData))
                    {
                        logParseError(line_number,line);
                    }
                }
                else if(keyword == "vt")
                {
                    stringstream>>whiteSpace>>std::ws;
                    //check
                    if(!std::isspace(whiteSpace) || stringstream.bad() || !parseTextureVertex(stringstream, meshData))
                    {
                        logParseError(line_number,line);
                    }
                }
                else if(keyword == "vn")
                {
                    stringstream>>whiteSpace>>std::ws;
                    //check
                    if(!std::isspace(whiteSpace) || stringstream.bad() || !parseNormal(stringstream, meshData))
                    {
                        logParseError(line_number,line);
                    }
                }
                else if((keyword == "f") || (keyword == "fo"))
                {
                    stringstream>>whiteSpace>>std::ws;
                    //check
                    if(!std::isspace(whiteSpace) || stringstream.bad() || !parseFace(stringstream, meshData))
                    {
                        logParseError(line_number,line);
                    }
                }
                else
                {
                    logParseError(line_number,line);
                }

            }

        }
    }
    
}

bool ObjMeshData::checkBound()const
{
    for(size_t faceIndex = 0; faceIndex < _faceLists.size(); ++faceIndex)
    {
        for(size_t faceVertexIndex = 0; faceVertexIndex < _faceLists[faceIndex].size(); ++ faceVertexIndex)
        {
            if(_faceLists[faceIndex][faceVertexIndex]._vIndex == -1)
            {
                CCLOG( "on face %d faceVertex %d, vIndex is -1 out of bound.", (int)faceIndex, (int)faceVertexIndex);
                return false;
            }
            if(_faceLists[faceIndex][faceVertexIndex]._vIndex >= _vertexLists.size())
            {
                CCLOG("on face %d faceVertex %d, vIndex is %d out of bound.", (int)faceIndex, (int)faceVertexIndex, _faceLists[faceIndex][faceVertexIndex]._vIndex);
                return false;
            }
            
            if(_faceLists[faceIndex][faceVertexIndex]._normIndex >= (int)_normalVertexLists.size())
            {
                CCLOG("on face %d faceVertex %d, normIndex is %d out of bound.", (int)faceIndex, (int)faceVertexIndex, _faceLists[faceIndex][faceVertexIndex]._normIndex);
                return false;
            }
            
            if(_faceLists[faceIndex][faceVertexIndex]._uvIndex >= (int)_uvVertexLists.size())
            {
                CCLOG("on face %d faceVertex %d, uvIndex is %d out of bound.", (int)faceIndex, (int)faceVertexIndex, _faceLists[faceIndex][faceVertexIndex]._uvIndex);
                return false;
            }
        }
    }
    
    return true;
}

bool ObjMeshData::isTriangeMesh() const
{
    for(const auto& face : _faceLists)
    {
        if(face.size() > 3)
            return false;
    }
    return true;
}

void ObjMeshData::triangular()
{
    checkBound();
    std::vector<std::vector<FaceVertex>> triangleFaces;
    for(const auto& face : _faceLists)
    {
        if(face.size() < 3) continue;
        else
        {
            //convert polygon to triangles
            // a,b, c,d,e will be converted into abc, acd, ade
            size_t triangleFacecount = face.size() - 2;
            for (size_t triangleIndex = 0; triangleIndex < triangleFacecount; ++triangleIndex)
            {
                std::vector<FaceVertex> triangle;
                triangle.push_back(face[0]);
                triangle.push_back(face[triangleIndex+1]);
                triangle.push_back(face[triangleIndex+2]);
                triangleFaces.push_back(triangle);
            }
        }
    }
    
    _faceLists = triangleFaces;
}

void ObjMeshData::trianglarAndGenerateNormals()
{
    triangular();
    if( _normalVertexLists.size() != 0 ) return;
    
    std::vector<std::vector<vec3>> faceVertexNormalList;
    faceVertexNormalList.resize(_vertexLists.size());
    
    for (const auto& face : _faceLists)
    {
        vec3 v1 = _vertexLists[face[0]._vIndex];
        vec3 v2 = _vertexLists[face[1]._vIndex];
        vec3 v3 = _vertexLists[face[2]._vIndex];
        
        vec3 fn = (v2-v1).Cross(v3-v2);
        fn.Normalize();
        faceVertexNormalList[face[0]._vIndex].push_back(fn);
        faceVertexNormalList[face[1]._vIndex].push_back(fn);
        faceVertexNormalList[face[2]._vIndex].push_back(fn);
    }
    
    _normalVertexLists.resize(faceVertexNormalList.size());
    for (int index = 0; index < _normalVertexLists.size(); ++index)
    {
        for (const auto& facenormal : faceVertexNormalList[index])
        {
            _normalVertexLists[index] += facenormal;
        }
        
        _normalVertexLists[index] /= faceVertexNormalList[index].size();
        _normalVertexLists[index].Normalize();
    }
}

void ObjMeshData::convertToRenderMesh(RenderMesh &renderMesh)
{
    trianglarAndGenerateNormals();
    int faceIndex(0);
    for(const auto&face : _faceLists)
    {
        renderMesh._indices.push_back(3 * faceIndex + 0);
        renderMesh._indices.push_back(3 * faceIndex + 1);
        renderMesh._indices.push_back(3 * faceIndex + 2);
        
        for (int faceVertexIndex = 0; faceVertexIndex < 3; ++faceVertexIndex)
        {
            RenderMesh::RenderVertex vertex;
            vertex.vertex = _vertexLists[face[faceVertexIndex]._vIndex];

            if(face[faceVertexIndex]._normIndex == -1)
                vertex.normal = _normalVertexLists[face[faceVertexIndex]._vIndex];
            else
                vertex.normal = _normalVertexLists[face[faceVertexIndex]._normIndex];
            
            if(face[faceVertexIndex]._uvIndex == -1)
                vertex.uv = vec2(0,0);
            else
                vertex.uv = _uvVertexLists[face[faceVertexIndex]._uvIndex];
            
            renderMesh._vertexs.push_back(vertex);
        }
        
        ++faceIndex;
    }
}

Mesh::Mesh(const string& name)
: _faceCount(0)
, _vertexCount(0)
, _texelCount(0)
{
    _name = FileUtils::getInstance()->fullPathForFilename(name);
    loadFromFile(name);
//
//    if (getTexelCount() > 0) {
//        _texels.resize(getTexelCount());
//    }
//    auto texel = _texels.begin();
//
//    _faces.resize(getTriangleIndexCount() / 3);
//    ifstream objFile(_name.c_str());
//    float dumy;
//    vector<Face>::iterator face = _faces.begin();
//    while (objFile) {
//        char c = objFile.get();
//        if (c == 'f' && objFile.get() == ' ') {
//            CCASSERT(face != _faces.end(), "parse error");
//            face->texi = ivec3(1,1,1);
//            objFile >> face->face.x;
//            if ((c = objFile.get()) == '/') {
//                objFile >> face->texi.x;
//                if ((c = objFile.get()) == '/')
//                    objFile >> dumy;
//            }
//            
//            objFile >> face->face.y;
//            if ((c = objFile.get()) == '/') {
//                objFile >> face->texi.y;
//                if ((c = objFile.get()) == '/')
//                    objFile >> dumy;
//            }
//            
//            objFile >> face->face.z;
//            if ((c = objFile.get()) == '/') {
//                objFile >> face->texi.z;
//                if ((c = objFile.get()) == '/') {
//                    objFile >> dumy;
//                }
//            }
//            if (c != '\n')
//                objFile.ignore(MAX_LINE_SIZE, '\n');
//            
//            face->face -= ivec3(1, 1, 1);
//            face->texi -= ivec3(1, 1, 1);
//            ++face;
//        }
//        else if (c == 'v') {
//            if ((c = objFile.get()) == 't') {
//                objFile >> texel->x >> texel->y;
//
//                /*while (texel->x >= 1.000) {
//                    texel->x -= 1.0;
//                }
//                while (texel->y >= 1.000) {
//                    texel->y -= 1.0;
//                }*/
////                texel->x = 1.0 - texel->x;
//                //if (texel->x > 1.0 || texel->y > 1.0) {
//                texel->y = 1.0 - texel->y;
//                ++texel;
//                //}
//            }
//            if (c != '\n')
//                objFile.ignore(MAX_LINE_SIZE, '\n');
//        }
//        else if (c != '\n')
//            objFile.ignore(MAX_LINE_SIZE, '\n');
//    }
//    CCASSERT(face == _faces.end(), "parse error");
}

Mesh::~Mesh()
{
}

bool Mesh::loadFromFile(const std::string &name)
{
    auto fileData = FileUtils::getInstance()->getDataFromFile(name);
    std::istringstream objFile((const char*)fileData.getBytes());
    
    ObjMeshParser parser;
    
    ObjMeshData data;
    parser.parse(objFile, data);
    
    data.convertToRenderMesh(_renderableMesh);
    return true;
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
    return _renderableMesh._indices.size()/3;
    if (_faceCount != 0)
        return _faceCount * 3;
    countVertexData();

    return _faceCount * 3;
}

void Mesh::generateVertices(vector<float>& floats, unsigned char flags) const
{
    floats.resize(_renderableMesh._vertexs.size() * 8);
    memcpy(&floats[0], &_renderableMesh._vertexs[0], _renderableMesh._vertexs.size() * 8 * sizeof(float));
}

void Mesh::generateTriangleIndices(vector<unsigned short>& indices) const
{
    indices = _renderableMesh._indices;
//    indices.resize(getTriangleIndexCount());
//    vector<unsigned short>::iterator index = indices.begin();
//    for (vector<Face>::const_iterator f = _faces.begin(); f != _faces.end(); ++f) {
//        *index++ = f->face.x;
//        *index++ = f->face.y;
//        *index++ = f->face.z;
//    }
}

NS_CC_END
