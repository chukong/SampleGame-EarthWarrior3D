
#ifndef __CCMESH_CACHE_H_
#define __CCMESH_CACHE_H_

#include <string>
#include <map>

class Mesh;
class MeshCache
{
public:
    MeshCache();
    virtual ~MeshCache();

    static MeshCache* getInstance();
    static void purgeMeshCache();

    Mesh* addMesh(const std::string& fileName);
    void removeMesh(const std::string& fileName);

    void reloadAllMeshes();

protected:
    static MeshCache* _cacheInstance;
    std::map<std::string, Mesh*> _cachedMeshes;
};

#endif // __CCMESH_CACHE_H_