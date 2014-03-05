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
        return true;
    }
    return false;
}
void Bullet::setVector(Point vec)
{
    _vector = vec;
}

Point Bullet::getVector()
{
    return _vector;
}