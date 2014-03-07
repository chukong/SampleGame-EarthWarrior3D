//
//  BulletController.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "BulletController.h"
#include "GameEntity.h"
#include "Bullet.h"
#include "consts.h"
#include "AirCraft.h"
#include "Effects.h"
#include "SimpleAudioEngine.h"
#include "Fodder.h"
#include "EnemyManager.h"

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
void BulletController::update(float dt)
{
    Point temp;
    Bullet* b;
    auto list =BulletController::bullets;
    for(int i = BulletController::bullets.size()-1; i >= 0; i-- )
    {
        b =BulletController::bullets.at(i);
        temp =b->getPosition();
        if(BOUND_RECT.containsPoint(temp))
        {
            for(int j = EnemyManager::sharedEnemyManager()->availabelEnemyVect.size()-1; j >= 0; j--)
            {
                auto e = EnemyManager::sharedEnemyManager()->availabelEnemyVect.at(j);
                if(b->getPosition().
                   getDistance(
                               e->getPosition()
                               ) <
                   (b->getRadius() + e->getRadius()))
                {
                    
                    //collision happened
                    if(b->getType() == kPlayerMissiles)
                    {
                        EffectManager::createExplosion(e->getPosition());
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom2.mp3");
                        //TODO: need to remove the expl when finished particle, or reuse
                    }
                    else
                    {
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
                        e->hurt(b->getDamage());
                        
                    }
                    
                    BulletController::erase(i);
                    break;
                }
            }
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
