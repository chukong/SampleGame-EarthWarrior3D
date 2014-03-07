//
//  AirCraft.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "AirCraft.h"
#include "SimpleAudioEngine.h"

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
}