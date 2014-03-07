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
    void move(float duration, const Point& position,int FodderNum);
    CREATE_FUNC(Fodder);
protected:
    
    const float rollSpeed = 3.5;// recommended 1.5
    float smoothAngle = 0.0f;
    
    float moveX;
    float moveY;
    
    const int cA = 10.0f;
    const int cB = 10.0f;
    const int cC = 0.0f;
    int fodderNum = 0;
    
    bool isMoving = false;
    float totalTime = 0;
    int nowTime = 1;
    const int amplitude = 80;
    
    
    Point endPosition;
    
    void update(float dt);
    void RemoveFodder(float dt);
};

#endif /* defined(__Moon3d__Fodder__) */
