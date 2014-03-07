//
//  BulletController.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "BulletController.h"
#include "Bullet.h"
#include "consts.h"

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
            bullet->retain();
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
        bullet->release();
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
    for(int i = BulletController::bullets.size()-1; i >= 0; i-- )
    {
        b =BulletController::bullets.at(i);
        temp =b->getPosition();
        if(!BOUND_RECT.containsPoint(temp))
        {
            BulletController::erase(i);
        }
        else{
            if(b->getType() == kPlayerMissiles)
            {
                b->update(dt);
            }
            else{
                b->setPosition(temp+(b->getVector()*dt));
            }
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
        b->removeFromParentAndCleanup(true);
        BulletController::bullets.erase(i);
    }
}
