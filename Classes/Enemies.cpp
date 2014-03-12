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
        _HP = 30;
        _radius = 40;
        
        
        return true;
    }
    return false;
}

void BigDude::reset()
{
    AirCraft::reset();
    _HP = 30;
    //_targetPos = nullptr;
}

void BigDude::showFinished()
{
    //remove from show Vector, add to the enemy Vector
    EnemyController::enemies.pushBack(this);
    EnemyController::showCaseEnemies.eraseObject(this);
    schedule(schedule_selector(BigDude::shoot),CCRANDOM_0_1()*2+1, 90, 0);
}
void BigDude::shoot(float dt)
{
    //Point bulletVec = Point(getRotation())
    Point offset1 = getPosition();
    Point offset2 = offset1;
    float angle = CC_DEGREES_TO_RADIANS(-getRotation()+90);
    float offsetRad = CC_DEGREES_TO_RADIANS(45);
    offset1.x += cosf(angle+offsetRad)*-50;
    offset1.y += sinf(angle+offsetRad)*-50;
    offset2.x += cosf(angle-offsetRad)*-50;
    offset2.y += sinf(angle-offsetRad)*-50;
    
    auto bullet =BulletController::spawnBullet(kEnemyBullet, offset1, Point(cosf(angle)*-500, sinf(angle)*-500));
    bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
    bullet =BulletController::spawnBullet(kEnemyBullet, offset2, Point(cosf(angle)*-500, sinf(angle)*-500));
    bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
}

void BigDude::update(float dt, Node* player)
{
    //find angle difference
    float angleRad = (getPosition()-player->getPosition()).getAngle();
    float angleDeg = -CC_RADIANS_TO_DEGREES(angleRad)+180;
    float curRot = getRotation();
    float angleDif = std::min(std::max((angleDeg-90) - curRot, -_turnRate*dt), _turnRate*dt);
    
    float f = curRot + angleDif;
    setRotation(f);
}