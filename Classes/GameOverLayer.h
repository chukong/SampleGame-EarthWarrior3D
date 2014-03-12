//
//  GameOverLayer.h
//  Moon3d
//
//  Created by Jacky on 14-3-12.
//
//

#ifndef __Moon3d__GameOverLayer__
#define __Moon3d__GameOverLayer__

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public LayerColor
{
public:
    
    static GameOverLayer* create(int score);
    
    virtual bool init();
    
private:
    
    int m_score;
    MenuItemImage* backtomenu_Item;
    MenuItemImage* playagain_Item;
    
    void ShowScore();
    
    void menu_backtomenu_Callback(Ref* sender);
    void menu_playagain_Callback(Ref* sender);
};

#endif /* defined(__Moon3d__GameOverLayer__) */
