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
#include "BulletController.h"
#include "consts.h"
#include "Bullet.h"
USING_NS_CC;

bool GameLayer::init()
{
    // variable init
    _collisionTree = new QuadTree(0, BOUND_RECT);
    
    
    spr = Sprite::create("groundLevel.jpg");
    addChild(spr);
    CCTexture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    spr->setScale(1.4);
    spr->setFlippedY(true);
    spr->setPosition(0.0f,400);
    
    _player = Player::create();
    _player->setPosition3D(Vertex3F(0,0,0));
    
    addChild(_player,10);
    
    _testDummy = Fodder::create();
    addChild(_testDummy);
    _testDummy->setPosition(0, 500);

    Vector<Node*> test;
    test.clear();
    
    
    
    BulletController::init(this);
    scheduleUpdate();
    return true;
}



void GameLayer::update(float dt){
    xScroll -= speed*dt;
    spr->setTextureRect(Rect(0,((int)xScroll)%2048,512,1200));
    for ( auto i : BulletController::bullets )
    {
        if(i->getPosition().getDistance(_testDummy->getPosition()) <
           (i->getRadius() + _testDummy->getRadius()))
        {
            log("hit");
        }
    }
    
    BulletController::update(dt);
    
    _collisionTree->clear();
}
