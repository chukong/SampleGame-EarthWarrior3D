//
//  ScrollingBackground.h
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#ifndef __Moon3d__GameLayer__
#define __Moon3d__GameLayer__
#include "cocos2d.h"
USING_NS_CC;
class Player;
class QuadTree;
class AirCraft;
class GameEntity;
class GameLayer : public Layer
{
public:
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(GameLayer);
protected:
    float xScroll = 0.0f;
    float speed = -60.0f;
    Sprite *spr;
    Player *_player;
    MotionStreak *_streak;

    int FodderNum = 0;
    void createCraft(float dt);
};
#endif /* defined(__Moon3d__GameLayer__) */