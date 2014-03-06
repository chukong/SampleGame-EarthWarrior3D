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
        _Model->setScale(10);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
                static_cast<Sprite3D*>(_Model)->setOutline(5.0, Color3B(0,0,0));
        _radius=40;
        _type = kEnemy;
        this->scheduleUpdate();
        return true;
    }
    return false;
}

void Fodder::move(float duration, const Point& position,int FodderNum)
{
    
    fodderNum = FodderNum;
    endPosition = position;
    moveX = this->getPosition3D().x;
    moveY = this->getPosition3D().y;
    totalTime = duration;
    isMoving = true;
    
    this->schedule(schedule_selector(Fodder::RemoveFodder) , duration, 1, 0.0);

    /*
    ccBezierConfig bezier; // 创建贝塞尔曲线
    bezier.controlPoint_1 = Point(this->getPosition3D().x,this->getPosition3D().y); // 起始点
    bezier.controlPoint_2 = Point(position.x > 1, this->getPosition3D().y>1); //控制点
    bezier.endPosition = position; // 结束位置
    
    BezierTo*  MoveDownOutScreen = BezierTo::create(duration,bezier);
    CallFuncN * callBack = CallFuncN::create(CC_CALLBACK_1(Fodder::RemoveFodder, this, FodderNum));
    
    this->runAction(Sequence::create(MoveDownOutScreen,callBack,NULL));
     */
}
/*
void Fodder::acrobacy(float dt)
{
   
}
 */
void Fodder::update(float dt)
{
    
    if (!isMoving)
    {
        return;
    }
    
    this->setRotation3D(Vertex3F(0,smoothAngle,0));
    smoothAngle+=rollSpeed;

    
    if(nowTime == amplitude)
    {
        nowTime = -1;
    }
    
    if(nowTime == -amplitude)
    {
        nowTime = 1;
    }
    
    if (nowTime<amplitude && nowTime>0)
    {
        nowTime ++;
       this->setPosition3D(Vertex3F(this->getPosition3D().x+5,this->getPosition3D().y-5,this->getPosition3D().z));
    }
    else if (nowTime> -amplitude*2 && nowTime<0)
    {
        nowTime --;
       this->setPosition3D(Vertex3F(this->getPosition3D().x-5,this->getPosition3D().y-5,this->getPosition3D().z));
    }
    
}
void Fodder::RemoveFodder(float dt)
{
    this->retain();
    this->removeFromParentAndCleanup(false);
    EnemyManager * aEnemyManager = EnemyManager::sharedEnemyManager();
    aEnemyManager->fodderAvilabelStateVect[fodderNum] = -aEnemyManager->fodderAvilabelStateVect[fodderNum];
    isMoving = false;
}
/*
void Fodder::RemoveFodder(Node* sender, int num)
{
    this->retain();
    this->removeFromParentAndCleanup(false);
    EnemyManager * aEnemyManager = EnemyManager::sharedEnemyManager();
    aEnemyManager->fodderAvilabelStateVect[num] = -aEnemyManager->fodderAvilabelStateVect[num];
}
*/