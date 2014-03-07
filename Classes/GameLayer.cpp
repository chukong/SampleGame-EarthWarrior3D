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
#include "BulletController.h"
#include "consts.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "Effects.h"
#include "GameEntity.h"
USING_NS_CC;
using namespace std;

bool GameLayer::init()
{
    // variable init
    //_collisionTree = new QuadTree(0, BOUND_RECT);
    
    
    spr = Sprite::create("groundLevel.jpg");
    addChild(spr);
    CCTexture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    spr->setScale(1.4);
    //spr->setFlippedY(true);
    spr->setPosition(0.0f,400.0f);
    
    _player = Player::create();
    _player->setPosition3D(Vertex3F(0,0,0));
    
    addChild(_player,10);
    

    _testDummy = Fodder::create();
    addChild(_testDummy);
    _testDummy->setPosition(0, 500);

    Vector<Node*> test;
    test.clear();

    this->schedule(schedule_selector(GameLayer::createCraft) , 1.0, -1, 0.0);

    BulletController::init(this);
    scheduleUpdate();
    
    return true;
}

void GameLayer::createCraft(float dt)
{
    EnemyManager * aEnemyManager = EnemyManager::sharedEnemyManager();
    if(0 == aEnemyManager->standByEnemyVect.size())
    {
        return;
    }
    int randStandByEnemy= rand()%aEnemyManager->standByEnemyVect.size();

    float positionX;
    int randomPositionNum = rand()%3;
    switch (randomPositionNum)
    {
        case 0:
            positionX = -300;
            break;
        case 1:
            positionX = -100;
            break;
        case 2:
            positionX = 100;
            break;
        case 3:
            positionX = 300;
            break;
        default:
            break;
    }
   
    Fodder * enemy = static_cast<Fodder *>(aEnemyManager->standByEnemyVect.at(randStandByEnemy));
    enemy->setPosition(positionX,800.0f);
    this->addChild(enemy);
    
    aEnemyManager->availabelEnemyVect.pushBack(aEnemyManager->standByEnemyVect.at(randStandByEnemy));
    //aEnemyManager->standByEnemyVect.at(randStandByEnemy)->retain();
    aEnemyManager->standByEnemyVect.eraseObject(static_cast<Node *>(aEnemyManager->standByEnemyVect.at(randStandByEnemy)),false);
    
    int idx = aEnemyManager->availabelEnemyVect.size()-1;
    enemy->move(Point(enemy->getPosition3D().x,-visible_size_macro.height*0.5),aEnemyManager->availabelEnemyVect.at(idx));
}

void GameLayer::update(float dt)
{
    xScroll += speed*dt;
    spr->setTextureRect(Rect(0,((int)xScroll)%2048,512,1200));
    for ( auto i : BulletController::bullets )
    {
        if(i->getPosition().getDistance(_testDummy->getPosition()) <
           (i->getRadius() + _testDummy->getRadius()))
        {

            //collision happened
            if(i->getType() == kPlayerMissiles)
            {
                auto expl = ExplosionFX::create();
                expl->setPosition(_testDummy->getPosition());
                addChild(expl);
                //TODO: need to remove the expl when finished particle, or reuse
            }

            BulletController::erase(i);
        }
    }
    BulletController::update(dt);
    //_collisionTree->clear();
}


