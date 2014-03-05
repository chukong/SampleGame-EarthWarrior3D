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
    void move(float duration, const Point& position);
    CREATE_FUNC(Fodder);
protected:
    void update(float dt);
    //void acrobacy(float dt);
    void RemoveFodder();
    const float rollSpeed = 3.5;// recommended 1.5
    float smoothAngle = 0.0f;
};

#endif /* defined(__Moon3d__Fodder__) */
