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
void BulletController::spawnBullet(int type, Point pos, Point vec)
{
    Bullet *bullet = nullptr;
    switch(type)
    {
        case kPlayerBullet:
            bullet = Bullet::create();
            bullet->setType(kPlayerBullet);
            break;
    }
    if(bullet)
    {
        BulletController::bullets.pushBack(bullet);
        BulletController::_bulletLayer->addChild(bullet);
        bullet->setPosition(pos);
        bullet->setVector(vec);
    }
}
void BulletController::update(float dt)
{

    Point temp;
    for ( auto &i : BulletController::bullets )
    {
        //remove bullets if its out of the screen
        temp =i->getPosition();
        if(!BOUND_RECT.containsPoint(temp))
        {
            BulletController::erase(i);
        }
        else
        {
            // update bullets position
            i->setPosition(temp+(i->getVector()*dt));
        }
    }
}
void BulletController::erase(Bullet* b)
{
    b->removeFromParent();
    BulletController::bullets.eraseObject(b);
}
