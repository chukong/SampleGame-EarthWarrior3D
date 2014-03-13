//
//  MainMenuScene.cpp
//  Moon3d
//
//  Created by Rye on 14-3-12.
//
//

#include "MainMenuScene.h"
#include "LoadingScene.h"
#include "PublicApi.h"
#include "Plane.h"
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
    plane = Plane::create();
    //plane->setPosition(visible_size_macro.width/2+100,visible_size_macro.height/2);
    this->addChild(plane, 10);
    this->scheduleUpdate();
    
    //************ adds stars ****************
    auto stars = ParticleSystemQuad::create("vanishingPoint.plist");
    stars->setAnchorPoint(Point(0.5f,0.5f));
    stars->setPosition(visible_size_macro.width-50,visible_size_macro.height/2 +40);
//    stars->setTotalParticles(8);
//    stars->setEmissionRate(9999999999);
//    stars->setScale(0.7);
//    stars->setTotalParticles(5);
//    stars->setEmissionRate(9999999999);
    this->addChild(stars,1,1);
    
    //************* adds background ***********
    auto background = Sprite::create("mainmenu_BG.png");
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,-1,-1);
    
    //************* adds logo *****************
    auto logo = Sprite::create("LOGO.png");
    logo->setAnchorPoint(Point(0.5,0.5));
    logo->setPosition(visibleSize.width/2,visibleSize.height-200);
    this->addChild(logo,3,3);
    
    //************* adds start game ***********
    auto startgame = MenuItemImage::create("start_game.png", "start_game.png", CC_CALLBACK_1(MainMenuScene::startgame, this));
    startgame->setPosition(visibleSize.width/2,200);
    
    //************* license *******************
    auto license = MenuItemImage::create("license.png", "license.png", CC_CALLBACK_1(MainMenuScene::license, this));
    license->setPosition(visibleSize.width/2-200,100);

    //************* credits ******************
    auto credits = MenuItemImage::create("credits.png", "credits.png", CC_CALLBACK_1(MainMenuScene::credits, this));
    credits->setPosition(visibleSize.width/2+200,100);

    auto menu = Menu::create(startgame,license,credits, NULL);
    menu->setPosition(origin);
    this->addChild(menu,3);
    
    return true;
}

void MainMenuScene::update(float dt){
    pRate+=0.01;
    plane->setPosition3D(Vertex3F(visible_size_macro.width/2+100,480-20*sin(1.05*pRate),0));
}

void MainMenuScene::startgame(Ref* sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(LoadingScene::createScene());
}

void MainMenuScene::credits(Ref* sender){
    
}

void MainMenuScene::license(Ref* sender){
    
}