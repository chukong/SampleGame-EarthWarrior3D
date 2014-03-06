//
//  Bullet.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "Bullet.h"
#include "3d/Sprite3D.h"
#include "consts.h"

bool Bullet::init()
{
    _Model = Sprite::create("CloseSelected.png");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerBullet;
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

bool Missile::init()
{
    _Model = Sprite3D::create("daodanv001.obj", "daodan_512.png");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerMissiles;
        _Model->setScale(3);
        _Model->setRotation3D(Vertex3F(90,0,0));
        static_cast<Sprite3D*>(_Model)->setOutline(0.3, Color3B(0,0,0));
        
        _left = (CCRANDOM_MINUS1_1()>0);
        if(_left)
            _yRotSpeed *= -1;
        return true;
    }
    return false;
}

void Missile::update(float dt)
{
    if(!_target)
    {
        //if missile has no target, try to lock onto an enemy
    }
    // missiles need to rotate
    _yRotation += _yRotSpeed*dt;
    _Model->setRotation3D(Vertex3F(90,_yRotation, 0));
}