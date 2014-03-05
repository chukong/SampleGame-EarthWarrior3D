//
//  Bullet.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "Bullet.h"

bool Bullet::init()
{
    _Model = Sprite::create("CloseSelected.png");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        scheduleUpdate();
        return true;
    }
    return false;
}

void Bullet::update(float dt)
{
    setPositionY(getPositionY()+dt*1600);
}