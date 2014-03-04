//
//  AirCraft.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__AirCraft__
#define __Moon3d__AirCraft__

#include "cocos2d.h"
#include "GameEntity.h"
USING_NS_CC;

class AirCraft : public GameEntity
{
public:
    void hurt(float damage);
    float getHP();
    void die();
    virtual void shoot();
protected:
    float _HP;// hit points
    
};

#endif /* defined(__Moon3d__AirCraft__) */
