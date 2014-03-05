//
//  GameEntity.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__GameEntity__
#define __Moon3d__GameEntity__

#include "cocos2d.h"

USING_NS_CC;

class GameEntity : public Node
{
public:
    CREATE_FUNC(GameEntity);
    Node *getModel();
    void remove();
    Vertex3F getOrientation();
    float getRadius(){return _radius;};
protected:
    Node *_Model;
    float _radius;
    Vertex3F _orientation;
};


#endif /* defined(__Moon3d__GameEntity__) */
