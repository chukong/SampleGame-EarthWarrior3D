//
//  QuadTree.h
//  Moon3d
//
//  Created by Hao Wu on 2/28/14.
//
//

#ifndef __Moon3d__QuadTree__
#define __Moon3d__QuadTree__

#include "cocos2d.h"

USING_NS_CC;

#define QUADTREE_MAX_OBJ 10
#define QUADTREE_MAX_LVL 5
class GameEntity;
class QuadTree
{
public:
    void clear(); // clear the node and all its child nodes
    void split(); // split to 4 child nodes
    int getIndex(GameEntity *entity); // determine which node it belongs to
    void insert(GameEntity *entity);
    Vector<GameEntity*> retrieve(Vector<GameEntity*> list, GameEntity *entity);
    QuadTree(int lvl, Rect rect);
protected:
    int _lvl=0; // current level, 0 is top
    Vector<GameEntity*> _entities; // holding game objects
    Rect _rect;
    QuadTree * _nodes[4];
};

#endif /* defined(__Moon3d__QuadTree__) */
