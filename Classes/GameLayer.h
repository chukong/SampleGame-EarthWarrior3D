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
    
    GameEntity *_testDummy;
protected:
    float xScroll = 0.0f;
    float speed = -60.0f;
    float fodderSpeed = 4.0f;
    Sprite *spr;
    Player *_player;

    QuadTree *_collisionTree;
    


    QuadTree *container;
    void createCraft(float dt);
};
#endif /* defined(__Moon3d__GameLayer__) */