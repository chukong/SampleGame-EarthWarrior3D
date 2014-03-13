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
#include "Plane.h"
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
    Plane* plane;
    float pRate = 3.1415926/2;

};

#endif /* defined(__Moon3d__MainMenuScene__) */
