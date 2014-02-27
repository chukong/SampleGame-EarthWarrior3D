//
//  ScrollingBackground.h
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#ifndef __Moon3d__ScrollingBackground__
#define __Moon3d__ScrollingBackground__
#include "cocos2d.h"


class ScrollBack : public cocos2d::Layer
{
public:
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(ScrollBack);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
protected:
    float xScroll = 0.0f;
    float speed = -60.0f;
    cocos2d::Sprite *spr;
    cocos2d::Sprite3D *player;
};
#endif /* defined(__Moon3d__ScrollingBackground__) */