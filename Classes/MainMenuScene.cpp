//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
#include "LoadingScene.h"
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Star_Chaser.mp3");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //************* adds background ***********
    auto background = Sprite::create("loading_bk.png");
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,-1,-1);
    
    //************* adds start game ***********
    auto startgame = MenuItemImage::create("start_game.png", "start_game.png", CC_CALLBACK_1(MainMenuScene::startgame, this));
    startgame->setPosition(visibleSize.width/2,200);
    
    //************* license *******************
    auto license = MenuItemImage::create("license.png", "license.png", CC_CALLBACK_1(MainMenuScene::license, this));
    license->setPosition(visibleSize.width/2-200,100);

    //************* quitgame ******************
    auto credits = MenuItemImage::create("credits.png", "credits.png", CC_CALLBACK_1(MainMenuScene::credits, this));
    credits->setPosition(visibleSize.width/2+200,100);

    auto menu = Menu::create(startgame,license,credits, NULL);
    menu->setPosition(origin);
    this->addChild(menu);
    
    return true;
}

void MainMenuScene::startgame(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(LoadingScene::createScene());
}

void MainMenuScene::credits(Ref* sender){
    
}

void MainMenuScene::license(Ref* sender){
    
}