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
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void Fodder::move(const Point& position,cocos2d::Node * enemy)
{
    fodder = enemy;
    endPosition = position;
    totalTime = abs(getPositionY()-endPosition.y)/fodderSpeed/60;
    perPeriodTime = totalTime*percent;
    sW = 2*Pi/perPeriodTime;
    rollSpeed = maxRotationAngle*4/perPeriodTime;
    isMoving = true;
    
    this->schedule(schedule_selector(Fodder::RemoveFodder) , totalTime, 1, 0.0);
}
void Fodder::update(float dt)
{
    if (!isMoving)
    {
        return;
    }
    
    if (smoothAngle+rollSpeed>maxRotationAngle)
    {
        isRevert = true;
    }
    
    if (smoothAngle-rollSpeed<-maxRotationAngle)
    {
        isRevert = false;
    }
    
    if (!isRevert)
    {
        smoothAngle+=rollSpeed;
    }
    else
    {
        smoothAngle-=rollSpeed;
    }
    float fY = this->getPositionY()-fodderSpeed;
    float fX = sA*sin(fY*sW);
    this->setPosition(Point(fX,fY));
    
    this->setRotation3D(Vertex3F(0,smoothAngle,0));
}
void Fodder::RemoveFodder(float dt)
{
    this->retain();
    this->removeFromParentAndCleanup(false);
    EnemyManager * aEnemyManager = EnemyManager::sharedEnemyManager();
    
    aEnemyManager->standByEnemyVect.pushBack(fodder);
    aEnemyManager->availabelEnemyVect.eraseObject(fodder,false);
    isMoving = false;
}
