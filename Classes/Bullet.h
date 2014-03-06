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

class Missile : public Bullet
{
public:
    CREATE_FUNC(Missile);
    bool init();
    void update(float dt);
    CC_SYNTHESIZE(GameEntity*, _target, Target)
protected:
    float _accel = 10;
    float _turnRate = 100;
    float _maxSpeed = 100;
    float _yRotSpeed = 1400;
    float _yRotation = 0;
    bool _left = false;
};

#endif /* defined(__Moon3d__Bullet__) */
