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

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
    
private:
    void startgame();
};

#endif /* defined(__Moon3d__MainMenuScene__) */
