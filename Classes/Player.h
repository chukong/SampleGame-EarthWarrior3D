/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://github.com/chukong/EarthWarrior3D
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    void setTargetPos(Vector2 target){targetPos = target;};
    
    void shoot(float dt);
    void shootMissile(float dt);
    void stop();
    CC_SYNTHESIZE(MotionStreak*, _streak, Trail);
    CC_SYNTHESIZE(ParticleSystemQuad*, _emissionPart, EmissionPart);
    void setPosition(Vector2 pos);
    virtual bool hurt(float damage);
    virtual void die();
    void hideWarningLayer();
protected:
    float targetAngle = 0;
    Vector2 targetPos = Vector2(0,0);
    Vector2 _trailOffset = Vector2(0,-40);
    
};


#endif /* defined(__Moon3d__Player__) */
