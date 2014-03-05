//
//  Player.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Player.h"
#include "Bullet.h"

bool Player::init()
{
    _Model = Sprite3D::create("playerv001.obj", "playerv002_1024.png");
    //_Model = Sprite3D::create("Scania4.obj", "car00.png");
    if(_Model)
    {
        _Model->setScale(30.8);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
        _radius = 40;
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        scheduleUpdate();
        static_cast<Sprite3D*>(_Model)->setOutline(5.0, Color3B(0,0,0));
        schedule(schedule_selector(Player::shoot), 0.1, -1, 0);
        return true;
    }
    return false;
}
void Player::update(float dt)
{
    float smoothedAngle =fmin(fmax(targetAngle*(1-dt*returnSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll)),-maxRoll),maxRoll);
    setRotation3D(Vertex3F(fabsf(smoothedAngle)*0.15,smoothedAngle, 0));
    targetAngle = getRotation3D().y;
    
}
bool Player::onTouchBegan(Touch *touch, Event *event)
{
    
    return true;
}
void Player::onTouchMoved(Touch *touch, Event *event)
{
    Point prev = event->getCurrentTarget()->getPosition();
    Point delta =touch->getDelta();
    
    setTargetAngle(targetAngle+delta.x*rollSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll));
    
    Point shiftPosition = delta+prev;
  
    setPosition(shiftPosition.getClampPoint(Point(-200,-376),Point(206,737)));
}
void Player::onTouchEnded(Touch *touch, Event *event)
{
}

void Player::shoot(float dt)
{
    auto projectile = Bullet::create();
    getParent()->addChild(projectile);
}