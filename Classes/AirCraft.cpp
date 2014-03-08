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

void AirCraft::hurt(float damage)
{
    _HP -= damage;
    if(_HP <= 0)
    {
        die();
    }
}
void AirCraft::die()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("boom.mp3");
    EffectManager::createBigExplosion(getPosition());
    _alive = false;
    //removeFromParent();
}

void AirCraft::move(Point pos)
{
    setPosition(getPosition()+pos);
}

void AirCraft::reset()
{
    _alive = true;
}
bool AirCraft::alive()
{
    return _alive;
}