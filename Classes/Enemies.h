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

class Fodder : public AirCraft
{
public:
    CREATE_FUNC(Fodder);
    bool init();
    virtual void reset();
};

class FodderLeader : public AirCraft
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
