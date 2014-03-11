#include "MeshCache.h"
#include "Mesh.h"
#include "cocos2d.h"

using namespace cocos2d;

MeshCache* MeshCache::_cacheInstance = nullptr;

typedef std::map<std::string, Mesh*>::iterator MeshMapIter;

MeshCache::MeshCache()
{
    
}

MeshCache::~MeshCache()
{
    for (auto iter = _cachedMeshes.begin(); iter != _cachedMeshes.end(); ++iter) {
        CC_SAFE_DELETE(iter->second);
    }
    _cachedMeshes.clear();
}

MeshCache* MeshCache::getInstance()
{
    if (! _cacheInstance) {
        _cacheInstance = new MeshCache();
    }
    
    return _cacheInstance;
}

void MeshCache::purgeMeshCache()
{
    if (_cacheInstance) {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

Mesh* MeshCache::addMesh(const std::string& fileName)
{
    Mesh* ret = nullptr;
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    MeshMapIter it = _cachedMeshes.find(fullPath);
    if (it == _cachedMeshes.end()) {
        ret = new Mesh(fileName);
        _cachedMeshes.insert(std::make_pair(fullPath, ret));
    }
    else
    {
        ret = it->second;
    }

    return ret;
}

void MeshCache::removeMesh(const std::string& fileName)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    MeshMapIter it = _cachedMeshes.find(fullPath);
    if (it != _cachedMeshes.end()) {
        CC_SAFE_DELETE(it->second);
        _cachedMeshes.erase(it);
    }
}

void MeshCache::reloadAllMeshes()
{
    for (auto iter = _cachedMeshes.begin(); iter != _cachedMeshes.end(); ++iter) {
        Mesh* mesh = iter->second;
        mesh->loadFromFile(iter->first);
    }
}
