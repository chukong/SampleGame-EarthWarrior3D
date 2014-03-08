//
//  BulletController.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "GameControllers.h"
#include "GameEntity.h"
#include "Bullets.h"
#include "consts.h"
#include "AirCraft.h"
#include "Effects.h"
#include "SimpleAudioEngine.h"
#include "Enemies.h"

Node* BulletController::_bulletLayer = nullptr;
bool BulletController::_inited = false;
Vector<Bullet*> BulletController::bullets;
Vector<Missile*> BulletController::_missilePool;



void BulletController::reset(){
    BulletController::_inited = false;
    BulletController::_bulletLayer = nullptr;
    BulletController::bullets.clear();
}
bool BulletController::init(Node *bulletLayer){
    if(bulletLayer)
    {
        BulletController::reset();
        BulletController::_bulletLayer = bulletLayer;
        BulletController::_inited = false;
        return true;
    }
    return false;
}
Bullet* BulletController::spawnBullet(int type, Point pos, Point vec)
{
    Bullet *bullet = nullptr;
    switch(type)
    {
        case kPlayerBullet:
            bullet = PlayerBullet::create();
            //bullet->retain();
            //bullet->setType(kPlayerBullet);
            break;
        case kPlayerMissiles:
            if(!_missilePool.empty())
            {
                // if the pool is not empty, we don't need to create, just return that, and reset its data
                bullet = _missilePool.back();
                bullet->retain();
                _missilePool.popBack();

                //bullet->reset();
            }
            else
            {
                bullet = Missile::create();
                bullet->retain();
            }
            //bullet->setType
            break;
    }
    if(bullet)
    {
        BulletController::bullets.pushBack(bullet);
        BulletController::_bulletLayer->addChild(bullet);
        //bullet->release();
        bullet->setPosition(pos);
        bullet->setVector(vec);
        return bullet;
    }
    return nullptr;
}
void BulletController::erase(Bullet* b)
{
    if(b->getType() == kPlayerMissiles)
    {
        BulletController::_missilePool.pushBack(static_cast<Missile*>(b));
        BulletController::bullets.eraseObject(b);
        b->removeFromParentAndCleanup(false);
        b->reset();
    }
    else
    {
        b->removeFromParentAndCleanup(true);
        BulletController::bullets.eraseObject(b);
    }
}
void BulletController::erase(int i)
{
    auto b = BulletController::bullets.at(i);
    if(b->getType() == kPlayerMissiles)
    {
        BulletController::_missilePool.pushBack(static_cast<Missile*>(b));
        BulletController::bullets.erase(i);
        b->removeFromParentAndCleanup(false);
        b->reset();
    }
    else
    {

        BulletController::bullets.erase(i);
        b->removeFromParentAndCleanup(false);
    }
}


Node* EnemyController::_enemyLayer = nullptr;
bool EnemyController::_inited = false;
Vector<AirCraft*> EnemyController::enemies;
Vector<Fodder*> EnemyController::_fodderPool;
Vector<FodderLeader*> EnemyController::_fodderLPool;
Vector<BigDude*> EnemyController::_bigDudePool;

const Point EnemyController::EnemyMoveDist = Point(0,-400);

bool EnemyController::init(Node* enemyLayer)
{
    EnemyController::_enemyLayer = enemyLayer;
    EnemyController::_inited = true;
    return true;
}

void EnemyController::reset()
{
    EnemyController::_inited = false;
    EnemyController::_enemyLayer = nullptr;
    EnemyController::enemies.clear();
}

AirCraft* EnemyController::spawnEnemy(int type)
{
    CC_ASSERT(EnemyController::_enemyLayer);
    AirCraft *enemy = nullptr;
    switch(type)
    {
        case kEnemyFodder:
            if(!_fodderPool.empty())
            {
                enemy = _fodderPool.back();
                enemy->retain();
                _fodderPool.popBack();
            }
            else
            {
                enemy = Fodder::create();
                enemy->retain();
            }
            break;
        case kEnemyFodderL:
            if(!_fodderLPool.empty())
            {
                enemy = _fodderLPool.back();
                enemy->retain();
                _fodderLPool.popBack();
            }
            else
            {
                enemy = FodderLeader::create();
                enemy->retain();
            }
            break;
        case kEnemyBigDude:
            if(!_bigDudePool.empty())
            {
                enemy = _bigDudePool.back();
                enemy->retain();
                _bigDudePool.popBack();
            }
            else
            {
                enemy = BigDude::create();
                enemy->retain();
            }
            break;
    }
    if(enemy)
    {
        EnemyController::enemies.pushBack(enemy);
        enemy->release();
        EnemyController::_enemyLayer->addChild(enemy);
        return enemy;
    }
    return nullptr;
}
void EnemyController::erase(int i)
{
    auto e = EnemyController::enemies.at(i);
    int type = e->getType();
    switch(type)
    {
        case kEnemyFodder:
            EnemyController::_fodderPool.pushBack(static_cast<Fodder*>(e));
            break;
        case kEnemyFodderL:
            EnemyController::_fodderLPool.pushBack(static_cast<FodderLeader*>(e));
            break;
        case kEnemyBigDude:
            EnemyController::_bigDudePool.pushBack(static_cast<BigDude*>(e));
            break;
    }
    EnemyController::enemies.erase(i);
    e->removeFromParentAndCleanup(false);
    e->reset();
}


void GameController::update(float dt)
{
    Point temp;
    Bullet* b;
    auto list =BulletController::bullets;
    Point enemyMoveDist =EnemyController::EnemyMoveDist*dt;
    for(int i = BulletController::bullets.size()-1; i >= 0; i-- )
    {
        b =BulletController::bullets.at(i);
        temp =b->getPosition();
        if(BOUND_RECT.containsPoint(temp))
        {
            //********* Enemy Loop **********
            for(int j = EnemyController::enemies.size()-1; j >= 0; j--)
            {
                auto e = EnemyController::enemies.at(j);
                if(b->getPosition().getDistance(e->getPosition()) <(b->getRadius() + e->getRadius()))
                {
                    //collision happened
                    switch(b->getType())
                    {
                        case kPlayerMissiles:
                            EffectManager::createExplosion(e->getPosition());
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom2.mp3");
                            break;
                        default:
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
                            break;
                    }
                    e->hurt(b->getDamage());
                    BulletController::erase(i);
                    break;
                }

            }
            //*********** Enemy Loop ***************
            if(b->getType() == kPlayerMissiles)
            {
                b->update(dt);
            }
            else{
                b->setPosition(temp+(b->getVector()*dt));
            }
        }
        else
        {
            BulletController::erase(i);
        }
    }
    for(int k = EnemyController::enemies.size()-1; k>=0; k--)
    {
        auto enemy =EnemyController::enemies.at(k);
        if(!enemy->alive())
        {
            EnemyController::erase(k);
            //enemy->reset();
            break;
        }
        switch(enemy->getType())
        {
            case kEnemyBigDude:
                enemy->update(dt);
                break;
            default:
                enemy->move(enemyMoveDist);
                break;
        }
        if(!ENEMY_BOUND_RECT.containsPoint(enemy->getPosition()))
        {
            //enemy went out side, kill it
            EnemyController::erase(k);
        }
        //TODO: if enemy collide with player
        //if(enemy->getPosition().getDistance(<#const cocos2d::Point &other#>))
    }
}
