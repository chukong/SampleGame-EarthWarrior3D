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
    bool init();
    void move(const Point& position,AirCraft * enemy);
    CREATE_FUNC(Fodder);
protected:
    AirCraft* fodder;

    float aPositionX;
    float smoothAngle = 0;
    bool isMoving = false;
    Point endPosition;
    const float amplitudeFriction = 50;
    float movingPerPeriodTime;
    float timeCount = 0;
    const float fodderSpeed = 3.5f;
    float totalTime;
    const float sA = 200.0f;
    float sW;
    void update(float dt);
    void RemoveFodder(float dt);
    
    void die();
};

#endif /* defined(__Moon3d__Fodder__) */
