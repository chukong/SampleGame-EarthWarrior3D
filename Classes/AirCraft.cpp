//
//  AirCraft.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "AirCraft.h"
#include "SimpleAudioEngine.h"
#include "Effects.h"

bool AirCraft::hurt(float damage)
{
    _HP -= damage;
    if(_HP <= 0)
    {
        die();
        return true;
    }
    return false;
}
void AirCraft::die()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explodeEffect.mp3");
    EffectManager::createBigExplosion(getPosition());
    _alive = false;
    //removeFromParent();
}

void AirCraft::move(float y, float dt)
{
    //setPosition(getPosition().x+getPosition().y+y);
    forward(y);
}

void AirCraft::reset()
{
    _alive = true;
}
bool AirCraft::alive()
{
    return _alive;
}