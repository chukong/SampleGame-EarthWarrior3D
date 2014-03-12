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
#include "Effects.h"
USING_NS_CC;
using namespace std;

bool GameLayer::init()
{
    // variable init
    //_collisionTree = new QuadTree(0, BOUND_RECT);
    
    for (int i=0; i<10; i++) {
        SmallExplosion* smallExpl = SmallExplosion::create();
        smallExpl->retain();
        BigExplosion* bigExpl = BigExplosion::create();
        bigExpl->retain();
        EffectManager::_smallExplPool.pushBack(smallExpl);
        EffectManager::_bigExplPool.pushBack(bigExpl);
    }
    
    
    _spr = Sprite::create("groundLevel.jpg");
    addChild(_spr, -5);
    Texture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT};
    _spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    _spr->setScale(1.4);
    _spr->setPosition(0.0f,400.0f);
    
    _player = Player::create();
    
    _streak = MotionStreak::create(0.4, 1, 15, Color3B(82,255,253), "streak.png");
    _player->setTrail(_streak);
    addChild(_streak,3);
    _emissionPart = ParticleSystemQuad::create("emissionPart.plist");
    _player->setEmissionPart(_emissionPart);
    addChild(_emissionPart,4);
    _emissionPart->setPositionType(tPositionType::FREE);
    addChild(_player,5);
    EffectManager::setLayer(this);

    this->schedule(schedule_selector(GameLayer::gameMaster) , 1.5, -1, 0.0);

    BulletController::init(this);
    EnemyController::init(this);
    scheduleUpdate();
    
    
    _player->setPosition(Point(0,-1000));
    _player->runAction(Sequence::create(
                       Spawn::create(
                                     EaseBackOut::create(MoveTo::create(1.7,Point(0,-200))),
                                     EaseSineOut::create(RotateBy::create(1.7,Vertex3F(0,720,0))),
                                     nullptr
                                     ),
                       CallFunc::create(CC_CALLBACK_0(GameLayer::schedulePlayer,this)),nullptr));
    return true;
}

void GameLayer::schedulePlayer()
{
    _player->scheduleUpdate();
}
void GameLayer::gameMaster(float dt)
{
    _elapsed+=dt;
    int enemyCount =EnemyController::enemies.size();
    //if(_elapsed < 10 && enemyCount < 5)
    if(enemyCount < 5)
    {
        Point random = Point(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200);
        for(int i=0; i < 5; i++)
        {
            auto enemy1 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy1->setPosition(random + Point(60,60)*(i+1));
            static_cast<Fodder*>(enemy1)->setMoveMode(moveMode::kDefault);
            auto enemy2 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy2->setPosition(random + Point(-60,60)*(i+1));
            static_cast<Fodder*>(enemy2)->setMoveMode(moveMode::kDefault);
            enemy1->setRotation3D(Vertex3F(0,0,0));
            enemy2->setRotation3D(Vertex3F(0,0,0));
        }
        auto leader = EnemyController::spawnEnemy(kEnemyFodderL);
        leader->setPosition(random);
        leader->setRotation3D(Vertex3F(0,0,0));
        static_cast<FodderLeader*>(leader)->setMoveMode(moveMode::kDefault);
    }
    //else if(_elapsed < 20 && enemyCount <5)
    if(_elapsed > 4 && enemyCount <3)
    {
        Point random = Point(-400, BOUND_RECT.size.height/4*CCRANDOM_MINUS1_1()+350);
        for(int i=0; i < 3; i++)
        {
            float randomAngle = CCRANDOM_MINUS1_1()*70;
            auto enemy = EnemyController::spawnEnemy(kEnemyFodder);
            enemy->setPosition(random + Point(60,60)*(i+1));
            static_cast<Fodder*>(enemy)->setTurnRate(randomAngle*0.5);
            enemy->setRotation(-randomAngle-90);
            auto enemy2 = EnemyController::spawnEnemy(kEnemyFodder);
            enemy2->setPosition(random + Point(-60,60)*(i+1));
            static_cast<Fodder*>(enemy2)->setTurnRate(randomAngle*0.5);
            enemy2->setRotation(-randomAngle-90);
        }
        auto leader = EnemyController::spawnEnemy(kEnemyFodderL);
        leader->setPosition(random);
        static_cast<FodderLeader*>(leader)->setTurnRate(45);
        leader->setRotation(-45);
        //enemy->runAction(EaseBackOut::create(MoveTo::create(2, _player->getPosition())));
        static_cast<FodderLeader*>(leader)->setTarget(_player);
        leader->schedule(schedule_selector(FodderLeader::shoot),CCRANDOM_0_1()*1+1,90,0);
        
    }
    if(_elapsed > 10 && enemyCount < 4)
    {
        for(int q = 0; q< 2; q++)
        {
            //random if its from the top, left, or bottom
            int direction = CCRANDOM_0_1()*4;
            float rX, rY;
            switch(direction)
            {
                case 0://top
                    rY = BOUND_RECT.size.height/2+200;
                    rX = ENEMY_BOUND_RECT.size.width*CCRANDOM_0_1();
                    break;
                case 1://bottom
                    rY = -200;
                    rX = ENEMY_BOUND_RECT.size.width*CCRANDOM_0_1();
                    break;
                case 2://left
                    rY = ENEMY_BOUND_RECT.size.height*CCRANDOM_0_1();
                    rX = ENEMY_BOUND_RECT.origin.x;
                    break;
                case 3://right
                    rY = ENEMY_BOUND_RECT.size.height*CCRANDOM_0_1();
                    rX = ENEMY_BOUND_RECT.size.width;
                    break;
            }
            auto enemy = EnemyController::showCaseEnemy(kEnemyBigDude);
            //enemy->setPosition(Point(100*CCRANDOM_MINUS1_1(), BOUND_RECT.size.height/2+200));
            enemy->setPosition(rX,rY);
            Point targetPos =Point(BOUND_RECT.size.width/3*CCRANDOM_MINUS1_1(),BOUND_RECT.size.height/3*CCRANDOM_0_1());
            enemy->setScale(2*CCRANDOM_MINUS1_1()+2);
            float randomTime = CCRANDOM_0_1()*1+1;
            enemy->setRotation3D(Vertex3F(300,0,-CC_RADIANS_TO_DEGREES((enemy->getPosition()-targetPos).getAngle())+90));
            enemy->runAction(
                             Sequence::create(
                                              Spawn::create(
                                                            EaseSineOut::create(MoveTo::create(randomTime, targetPos)),
                                                            EaseSineOut::create(ScaleTo::create(randomTime,1)),//TODO: replace with move 3d when possible
                                                            EaseBackOut::create(RotateBy::create(randomTime+0.2,Vertex3F(-300,0,0))),
                                                            nullptr
                                                            ),
                                              CallFunc::create(enemy,callfunc_selector(BigDude::showFinished)),
                                              nullptr
                             ));
        }
    }
    if(_elapsed > 60)
    {
        //spawn boss
        
    }
}

void GameLayer::update(float dt)
{
    xScroll += speed*dt;
    _spr->setTextureRect(Rect(0,((int)xScroll)%2048,512,1200));
    //_cloud->setTextureRect(Rect(0,((int)xScroll)%1024, 256, 1024));
    GameController::update(dt, _player);
}


