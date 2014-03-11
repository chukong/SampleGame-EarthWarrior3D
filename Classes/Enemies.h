//
//  Fodder.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__Fodder__
#define __Moon3d__Fodder__

#include "cocos2d.h"
#include "AirCraft.h"
enum moveMode{
    kDefault,
    kTurn
};
class Fodder : public AirCraft
{
public:
    CREATE_FUNC(Fodder);
    bool init();
    virtual void reset();
    virtual void move(float y, float dt);
    CC_SYNTHESIZE(int, _moveMode, MoveMode);
    CC_PROPERTY(float, _turn, TurnRate);
    virtual void shoot(float dt);
    CC_SYNTHESIZE(AirCraft*, _target, Target);
};

class FodderLeader : public Fodder
{
public:
    CREATE_FUNC(FodderLeader);
    bool init();
    virtual void reset();
};

class BigDude : public AirCraft
{
public:
    CREATE_FUNC(BigDude);
    bool init();
    virtual void reset();
    void update(float dt);
protected:
    Point _targetPos;
};


#endif /* defined(__Moon3d__Fodder__) */
