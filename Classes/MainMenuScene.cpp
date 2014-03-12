//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //************* adds background ***********
    auto background = Sprite::create("loading_bk.png");
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,-1,-1);
    
    //************* adds start game ***********
    auto startgame = MenuItemImage::create("dd.png", "dd.png", CC_CALLBACK_1(MainMenuScene::startgame, this) );
    //MenuItemLabel::create(<#cocos2d::Node *label#>, <#const ccMenuCallback &callback#>)
    
    
    
    return true;
}

void MainMenuScene::startgame(){
    
}