//
//  GameOverLayer.cpp
//  Moon3d
//
//  Created by Jacky on 14-3-12.
//
//

#include "GameOverLayer.h"

GameOverLayer* GameOverLayer::create(int score)
{
	GameOverLayer *pRet = new GameOverLayer();
	pRet->m_score=score;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
    return pRet;
}

bool GameOverLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 50))) {
        return false;
    }
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    
    auto score_bk=Sprite::create("gameover_score_bk.png");
    score_bk->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    addChild(score_bk,1);
    score_bk->setScale(0.2f);
    score_bk->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f),
                                         ScaleTo::create(0.1f, 0.9f),
                                         ScaleTo::create(0.1f, 1.0f),
                                         CallFunc::create(this,callfunc_selector(GameOverLayer::ShowScore)),
                                         NULL));
    
    
    backtomenu_Item = MenuItemImage::create("gameover_backtomenu.png",
                                           "gameover_backtomenu.png",
                                           CC_CALLBACK_1(GameOverLayer::menu_backtomenu_Callback,this));
    
    playagain_Item = MenuItemImage::create("gameover_playagain.png",
                                           "gameover_playagain.png",
                                           CC_CALLBACK_1(GameOverLayer::menu_playagain_Callback,this));
    
    auto menu = Menu::create(backtomenu_Item,playagain_Item,NULL);
    menu->alignItemsHorizontallyWithPadding(20);
    menu->setPosition(visibleSize.width/2, 100);
    this->addChild(menu, 2);
    
    return true;
}

void GameOverLayer::ShowScore()
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    
    auto score_text=Sprite::create("gameover_score.png");
    score_text->setPosition(Point(-200, visibleSize.height/2+30));
    score_text->runAction(MoveTo::create(0.5f, Point(visibleSize.width/2,visibleSize.height/2+30)));
    addChild(score_text,2);
    
    char pScore[10];
    sprintf(pScore, "%d",m_score);
    auto score_label=LabelBMFont::create(pScore, "gameover_score_num.fnt");
    score_label->setAnchorPoint(Point(0.5f,0.5f));
    score_label->setPosition(Point(1000,visibleSize.height/2-40));
    score_label->runAction(Sequence::create(
                           MoveTo::create(0.5f, Point(visibleSize.width/2,visibleSize.height/2-30)),
                                            ScaleTo::create(0.1f, 1.3f),
                                            ScaleTo::create(0.1f, 0.98f),
                                            ScaleTo::create(0.1f, 1.2f),NULL));
    addChild(score_label,2);

}

void GameOverLayer::menu_backtomenu_Callback(Ref* sender)
{
    backtomenu_Item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                                ScaleTo::create(0.1f, 0.9f),
                                                ScaleTo::create(0.1f, 1.0f),NULL));
//    Director::getInstance()->replaceScene();
}

void GameOverLayer::menu_playagain_Callback(Ref* sender)
{
    playagain_Item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                                ScaleTo::create(0.1f, 0.9f),
                                                ScaleTo::create(0.1f, 1.0f),NULL));
}