//
//  QuadTree.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/28/14.
//
//

#include "QuadTree.h"
#include "GameEntity.h"
QuadTree::QuadTree(int lvl, Rect rect)
{
    _lvl = lvl;
    _rect = rect;
    for(int i = 0; i<4; i++)
    {
        _nodes[i]= NULL;
    }
}

void QuadTree::clear()
{
    _entities.clear();
    for(int i = 0; i<4; i++)
    {
        _nodes[i]->clear();
        delete _nodes[i];
        _nodes[i] = NULL;
    }
}

void QuadTree::split()
{
    float w = _rect.size.width/2;
    float h = _rect.size.height/2;
    float x = _rect.origin.x;
    float y = _rect.origin.y;
    _nodes[0] = new QuadTree(_lvl+1, Rect(x+w,y,w,h));
    _nodes[1] = new QuadTree(_lvl+1, Rect(x,y,w,h));
    _nodes[2] = new QuadTree(_lvl+1, Rect(x,y+h,w,h));
    _nodes[3] = new QuadTree(_lvl+1, Rect(x+w,y+h,w,h));
}

int QuadTree::getIndex(GameEntity * entity)
{
    Point pos = entity->getPosition();
    float radius = entity->getRadius();
    int index = -1;
    float verticalMid = _rect.size.width/2 + _rect.origin.x;
    float horizontalMid = _rect.size.height/2 + _rect.origin.y;
    
    bool top = (pos.y - radius > horizontalMid);
    bool bot = (pos.y + radius > horizontalMid);
    if(pos.x - radius > verticalMid)
    {
        if(top)
            index=1;
        else
            index=2;
    }
    else if(pos.x + radius < verticalMid)
    {
        if(top)
            index = 0;
        else if(bot)
            index = 3;
    }
    return index;
}

void QuadTree::insert(GameEntity *entity)
{
    if(_nodes[0]!= NULL)
    {
        int index = getIndex(entity);
        if(index != -1)
        {
            _nodes[index]->insert(entity);
            return;
        }
    }
    _entities.pushBack(entity);
    if(_entities.size() > QUADTREE_MAX_OBJ && _lvl < QUADTREE_MAX_LVL)
    {
        if(_nodes[0] == NULL){
            split();
        }
        int i = 0;
        while(i<_entities.size())
        {
            GameEntity *entity = _entities.at(i);
            int idx = getIndex(entity);
            if(idx != -1)
            {
                _nodes[idx]->insert(entity);
                _entities.erase(i);
            }
            else{
                i++;
            }
        }
    }
}

Vector<GameEntity*> QuadTree::retrieve(Vector<GameEntity*> list, GameEntity* entity)
{
    int index = getIndex(entity);
    if(index != -1 && _nodes[0])
    {
        _nodes[index]->retrieve(list, entity);
    }
    for(const auto &entity : _entities)
    {
        list.pushBack(entity);
    }
    return list;
}