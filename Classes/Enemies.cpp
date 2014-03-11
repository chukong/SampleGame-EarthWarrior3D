//
//  Fodder.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Enemies.h"
#include "3d/Sprite3D.h"
#include "GameControllers.h"
#include "Bullets.h"
#include "consts.h"

bool Fodder::init()
{
    _score = 10;
    _Model = Sprite3D::create("dijiyuanv001.obj", "dijiyuanv001.png");
    if(_Model)
    {
        _Model->setScale(6);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
        static_cast<Sprite3D*>(_Model)->setOutline(0.2, Color3B(0,0,0));
        _type = kEnemyFodder;
        _HP = 10;
        _radius = 30;
        return true;
    }
    return false;
}
void Fodder::reset()
{
    AirCraft::reset();
    _HP = 10;
}
void Fodder::setTurnRate(float turn)
{
    setMoveMode(moveMode::kTurn);
    setRotation3D(Vertex3F(fabsf(turn)*0.15, turn, 0));
    _turn = turn;
}
float Fodder::getTurnRate()
{
    return _turn;
}
void Fodder::move(float y, float dt)
{
switch(_moveMode)
    {
        case moveMode::kTurn:
            forward(y, getTurnRate()*dt);
            break;
        default:
            //setPosition(getPosition()+pos);
            forward(y);
    }

}
void Fodder::shoot(float dt)
{
    if(_target->alive())
    {
        //get angle to player;
        float angle = (getPosition()-_target->getPosition()).getAngle();
        auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Point(cosf(angle)*-500, sinf(angle)*-500));
        //auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Point(0,-500));
        bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
        log("aaaaaaa");
    }
    else{
        log("player is dead,hahahaha");
    }
}


bool FodderLeader::init()
{
    _score = 20;
    _Model = Sprite3D::create("dijiyuanv001.obj", "dijiyuanv001.png");
    if(_Model)
    {
        _Model->setScale(8);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
        static_cast<Sprite3D*>(_Model)->setOutline(0.2, Color3B(255,0,0));
        _type = kEnemyFodderL;
        _HP = 20;
        _radius = 35;
        return true;
    }
    return false;
}
void FodderLeader::reset()
{
    AirCraft::reset();
    _HP = 25;
}


bool BigDude::init()
{
    _score = 20;
    _Model = Sprite3D::create("diji1_v002.obj", "diji02_v002_128.png");
    if(_Model)
    {
        _Model->setScale(8);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
        static_cast<Sprite3D*>(_Model)->setOutline(0.2, Color3B(0,0,0));
        _type = kEnemyBigDude;
        _HP = 50;
        _radius = 40;
        
        
        return true;
    }
    return false;
}

void BigDude::reset()
{
    AirCraft::reset();
    _HP = 50;
    //_targetPos = nullptr;
}

void BigDude::update(float dt)
{
    
}