//
//  MainMenuScene.h
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#ifndef __Moon3d__MainMenuScene__
#define __Moon3d__MainMenuScene__

#include "cocos2d.h"
#include "3d/Sprite3D.h"
class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
    void update(float dt);
private:
    void startgame(cocos2d::Ref* sender);
    void license(cocos2d::Ref* sender);
    void credits(cocos2d::Ref* sender);
    Sprite3D* plane;
    float pRate = Pi/2;
    float originX = -9.0f;
    float originY = 159.0f;
    float originZ = 9.0f;
    const float pXW = 5.0f;
    const float pYW = 5.0f;
    const float pZW = 5.0f;
    const float pXA = 1.0f;
    const float pYA = 10.0f;
    const float pZA = 10.0f;
};

#endif /* defined(__Moon3d__MainMenuScene__) */
