//
//  ScrollingBackground.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#include "GameLayer.h"
#include "Player.h"
#include "Fodder.h"
#include "QuadTree.h"
#include "PublicApi.h"
USING_NS_CC;

bool GameLayer::init()
{
    // variable init
    container = new QuadTree(0, Rect(0,0, 100, 100));
    
    
    spr = Sprite::create("groundLevel.jpg");
    addChild(spr);
    CCTexture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    spr->setScale(1.4);
    spr->setFlippedY(true);
    spr->setPosition(0.0f,400.0f);
    
    _player = Player::create();
    _player->setPosition3D(Vertex3F(0,0,0));
    
    addChild(_player,10);
    
    this->schedule(schedule_selector(GameLayer::createCraft) , 2.0, -1, 0.0);
    scheduleUpdate();
    
    return true;
}

void GameLayer::createCraft(float dt)
{
    std::vector<int> startPointVec;
    startPointVec.push_back(-500);
    startPointVec.push_back(-300);
    startPointVec.push_back(-100);
    startPointVec.push_back(100);
    startPointVec.push_back(300);
    startPointVec.push_back(500);
    
    int vectSize = startPointVec.size();
    
    for (int i = 0; i<vectSize; i++)
    {
        int selectNum = rand()%startPointVec.size();
        int startPointX = startPointVec[selectNum];
        
        auto enemy = Fodder::create();
        addChild(enemy);
        enemy->setPosition(startPointX, 800.0f);
        container->insert(enemy);
        enemy->move(3.0,Point(enemy->getPosition3D().x,-visible_size_macro.height*1.5));
    }
}

void GameLayer::update(float dt){
    xScroll -= speed*dt;
    spr->setTextureRect(Rect(0,((int)xScroll)%2048,512,1200));
    //Point;
    //_player->setRotation3D(Vertex3F(0,xScroll,0));
}


