//
//  Bullet.h
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#ifndef __Moon3d__Bullet__
#define __Moon3d__Bullet__

#include "cocos2d.h"
#include "GameEntity.h"



class Bullet : public GameEntity
{
public:
    CREATE_FUNC(Bullet);
    bool init();
    void setVector(Point vec);
    Point getVector();
protected:
    Point _vector;
};

#endif /* defined(__Moon3d__Bullet__) */
