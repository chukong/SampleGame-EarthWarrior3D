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

USING_NS_CC;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
    
private:
    void startgame(cocos2d::Ref* sender);
    void license(cocos2d::Ref* sender);
    void credits(cocos2d::Ref* sender);
    
    void startgame_callback();
    void license_callback();
    void credits_callback();
    
private:
    MenuItemImage* startgame_item;
    MenuItemImage* license_item;
    MenuItemImage* credits_item;
};

#endif /* defined(__Moon3d__MainMenuScene__) */
