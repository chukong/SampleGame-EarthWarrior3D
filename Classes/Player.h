//
//  Player.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__Player__
#define __Moon3d__Player__

#include "cocos2d.h"
#include "AirCraft.h"


USING_NS_CC;

class Player : public AirCraft
{
public:
    CREATE_FUNC(Player);
    bool init();
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    void update(float dt);
    
    const float rollSpeed = 1.5;// recommended 1.5
    const float returnSpeed = 10;// recommended 4
    const float maxRoll = 75;
    const float rollReturnThreshold = 1.02;
    void setTargetAngle(float angle){targetAngle = angle;};
    void setTargetPos(Point target){targetPos = target;};
    
    virtual void shoot(float dt);
protected:
    float targetAngle = 0;
    Point targetPos = Point(0,0);
};


#endif /* defined(__Moon3d__Player__) */
