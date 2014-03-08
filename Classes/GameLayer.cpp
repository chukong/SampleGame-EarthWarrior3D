//
//  ScrollingBackground.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#include "GameLayer.h"
#include "Player.h"
#include "Enemies.h"
#include "PublicApi.h"
#include "GameControllers.h"
#include "consts.h"
#include "Bullets.h"
//#include "EnemyManager.h"
#include "Effects.h"
#include "GameEntity.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;

bool GameLayer::init()
{
    // variable init
    //_collisionTree = new QuadTree(0, BOUND_RECT);
    
    
    spr = Sprite::create("groundLevel.jpg");
    addChild(spr);
    Texture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    spr->setScale(1.4);
    //spr->setFlippedY(true);
    spr->setPosition(0.0f,400.0f);
    
    _player = Player::create();
    
    _streak = MotionStreak::create(0.4, 1, 15, Color3B(82,255,253), "streak.png");
    _player->setTrail(_streak);
    addChild(_streak);
    
    addChild(_player,10);
    EffectManager::setLayer(this);
    auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
    Audio->preloadEffect("boom.mp3");
    Audio->preloadEffect("hit.mp3");
    Audio->preloadEffect("boom2.mp3");

    this->schedule(schedule_selector(GameLayer::gameMaster) , 1.5, -1, 0.0);

    BulletController::init(this);
    EnemyController::init(this);
    scheduleUpdate();
    
    return true;
}

void GameLayer::gameMaster(float dt)
{
    _elapsed+=dt;
    //if(_elapsed < 10 && EnemyController::enemies.size() < 5)
    {
        Point random = Point(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200);
        for(int i=0; i < 4; i++)
        {
            EnemyController::spawnEnemy(kEnemyFodder)->setPosition(random + Point(60,60)*(i+1));
            EnemyController::spawnEnemy(kEnemyFodder)->setPosition(random + Point(-60,60)*(i+1));
        }
        EnemyController::spawnEnemy(kEnemyFodderL)->setPosition(random);
    }
}

void GameLayer::update(float dt)
{
    xScroll += speed*dt;
    spr->setTextureRect(Rect(0,((int)xScroll)%2048,512,1200));

    GameController::update(dt);
    //_collisionTree->clear();
    //_streak->setPosition(_player->getPosition()-Point(0,40));
}


