//
//  Player.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Player.h"

bool Player::init()
{
    _Model = Sprite3D::create("DownNecker.obj", "Done1.png");
    //_Model = Sprite3D::create("Scania4.obj", "car00.png");
    if(_Model)
    {
        _Model->setScale(1.3);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,90));
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        scheduleUpdate();
        
        return true;
    }
    return false;
}
void Player::update(float dt)
{
    //float target = getTargetAngle();
    //setRotation3D(Vertex3F(0,fmin(fmax(targetAngle*(1-dt*returnSpeed),-70),70), 0));
    setRotation3D(Vertex3F(0,fmin(fmax(targetAngle*(1-dt*returnSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll)),-maxRoll),maxRoll), 0));
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
    setPosition(delta+prev);

    setTargetAngle(targetAngle+delta.x*rollSpeed*(rollReturnThreshold-fabsf(targetAngle)/maxRoll));
}
void Player::onTouchEnded(Touch *touch, Event *event)
{
    
}