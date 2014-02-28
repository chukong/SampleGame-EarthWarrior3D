//
//  ScrollingBackground.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#include "GameLayer.h"

USING_NS_CC;

bool GameLayer::init()
{
    spr = Sprite::create("groundLevel.jpg");
    addChild(spr);
    CCTexture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    spr->setScale(1.4);
    spr->setFlippedY(true);
    spr->setPosition(0.0f,400);
    
    _player = Player::create();
    _player->setPosition3D(Vertex3F(0,0,0));
    
    addChild(_player,10);
    
    auto enemy = Fodder::create();
    addChild(enemy);
    enemy->setPosition(0, 500);
    Enemies.pushBack(enemy);
    
    scheduleUpdate();
    return true;
}



void GameLayer::update(float dt){
    xScroll -= speed*dt;
    spr->setTextureRect(Rect(0,xScroll,512,1200));
    //Point;
    for(const auto &enemy : Enemies) {
        float dist =(enemy->getPosition()-_player->getPosition()).getLength();
        float eRadius = enemy->getRadius();
        float pRadius = _player->getRadius();
        if(dist < (eRadius+pRadius))
        {
            log("touched");
        }
    }
    //_player->setRotation3D(Vertex3F(0,xScroll,0));
}
