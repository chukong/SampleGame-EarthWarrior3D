//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
#include "LoadingScene.h"
#include "GameLayer.h"
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
    startgame_item = MenuItemImage::create("start_game.png", "start_game.png", CC_CALLBACK_1(MainMenuScene::startgame, this));
    startgame_item->setPosition(visibleSize.width/2,200);
    
    //************* license *******************
    license_item = MenuItemImage::create("license.png", "license.png", CC_CALLBACK_1(MainMenuScene::license, this));
    license_item->setPosition(visibleSize.width/2-200,100);

    //************* quitgame ******************
    credits_item = MenuItemImage::create("credits.png", "credits.png", CC_CALLBACK_1(MainMenuScene::credits, this));
    credits_item->setPosition(visibleSize.width/2+200,100);

    auto menu = Menu::create(startgame_item,license_item,credits_item, NULL);
    menu->setPosition(origin);
    this->addChild(menu);
    
    return true;
}

void MainMenuScene::startgame(Ref* sender){
    startgame_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                                ScaleTo::create(0.1f, 0.9f),
                                                ScaleTo::create(0.1f, 1.0f),
                                               CallFunc::create(CC_CALLBACK_0(MainMenuScene::startgame_callback,this)),NULL));
}

void MainMenuScene::startgame_callback()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GameLayer::isDie=false;
    Director::getInstance()->replaceScene(LoadingScene::createScene());
}

void MainMenuScene::credits(Ref* sender){
    credits_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                               ScaleTo::create(0.1f, 0.9f),
                                               ScaleTo::create(0.1f, 1.0f),
                                             CallFunc::create(CC_CALLBACK_0(MainMenuScene::credits_callback, this)),NULL));
}

void MainMenuScene::credits_callback()
{
    
}

void MainMenuScene::license(Ref* sender){
    license_item->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f),
                                               ScaleTo::create(0.1f, 0.9f),
                                               ScaleTo::create(0.1f, 1.0f),
                                             CallFunc::create(CC_CALLBACK_0(MainMenuScene::license_callback, this)),NULL));
}

void MainMenuScene::license_callback()
{
    
}