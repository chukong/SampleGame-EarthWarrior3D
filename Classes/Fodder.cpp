//
//  Fodder.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Fodder.h"
#include "3d/Sprite3D.h"
#include "consts.h"
#include "PublicApi.h"
#include "EnemyManager.h"

using namespace std;

bool Fodder::init()
{
    _Model = Sprite3D::create("diji1_v001.obj", "diji02_v002_1024.png");
    if(_Model)
    {
        _Model->setScale(6);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
                static_cast<Sprite3D*>(_Model)->setOutline(0.14, Color3B(0,0,0));
        _radius=40;
        _type = kEnemy;
        _HP = 160;
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void Fodder::move(const Point& position,AirCraft * enemy)
{
    fodder = enemy;
    endPosition = position;
    totalTime = abs(getPositionY()-endPosition.y)/fodderSpeed/60;
    movingPerPeriodTime = totalTime*amplitudeFriction;
    sW = 2*Pi/movingPerPeriodTime;
    

    int randomPositionNum = rand()%3;
    switch (randomPositionNum)
    {
        case 0:
            aPositionX = -300;
            break;
        case 1:
            aPositionX = -100;
            break;
        case 2:
            aPositionX = 100;
            break;
        case 3:
            aPositionX = 300;
            break;
        default:
            break;
    }
    
    isMoving = true;
    
    this->schedule(schedule_selector(Fodder::RemoveFodder) , totalTime, 1, 0.0);
}
void Fodder::update(float dt)
{
    if (!isMoving)
    {
        return;
    }
    
    float fY = this->getPositionY()-fodderSpeed;
    float fX = sA*sin(fY*sW)+aPositionX;
    this->setPosition(Point(fX,fY));
   
    smoothAngle = -sin(fY*sW)*60;
    this->setRotation3D(Vertex3F(-fabsf(smoothAngle)*0.25,smoothAngle,-smoothAngle*0.25));
}
void Fodder::RemoveFodder(float dt)
{
    this->removeFromParentAndCleanup(false);
    EnemyManager * aEnemyManager = EnemyManager::sharedEnemyManager();
    
    aEnemyManager->standByEnemyVect.pushBack(fodder);
    aEnemyManager->availabelEnemyVect.eraseObject(fodder,false);
    isMoving = false;
}

void Fodder::die()
{
    _HP = 160;
}