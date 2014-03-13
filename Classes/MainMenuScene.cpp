//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
#include "LoadingScene.h"
//#include
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
    
    //************ adds Plane ****************
    plane = Sprite3D::create("playerv002.obj", "playerv002_256.png");
    plane->setPosition(visibleSize.width/2+100,visibleSize.height/2);
    plane->setScale(65);
    plane->setOutline(0.035, Color3B::BLACK);
    plane->setRotation3D(Vertex3F(originX,originY,originZ));
    this->addChild(plane);
    this->scheduleUpdate();
//    plane->runAction(Sequence::create(rotate, rotateBack,NULL));
    
    //************* adds background ***********
    auto background = Sprite::create("mainmenu_BG.png");
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,-1,-1);
    
    //************* adds logo *****************
    auto logo = Sprite::create("LOGO.png");
    logo->setAnchorPoint(Point(0.5,0.5));
    logo->setPosition(visibleSize.width/2,visibleSize.height-200);
    this->addChild(logo,0,0);

    
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

void MainMenuScene::update(float dt){
    pRate+=0.01;
    float x = originX-pXA*sin(pXW*pRate);
    float y = originY-pYA*sin(pYW*pRate);
    float z = originZ-pZA*sin(pZW*pRate);
    plane->setRotation3D(Vertex3F(x,y,z));
    
    plane->setPositionZ(0);
    log("x:%f y:%f z:%f \n",x,y,z);
}

void MainMenuScene::startgame(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(LoadingScene::createScene());
}

void MainMenuScene::credits(Ref* sender){
    
}

void MainMenuScene::license(Ref* sender){
    
}