//
//  GameEntity.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "GameEntity.h"

USING_NS_CC_MATH;

Node *GameEntity::getModel(){
    return _Model;
}

Vector3 GameEntity::getOrientation(){
    return _orientation;
}

void GameEntity::forward(float dist){
    float f = getRotation();
    setPosition(getPosition()
                +Vector2(
                       sinf(CC_DEGREES_TO_RADIANS(f))*dist,
                       cosf(CC_DEGREES_TO_RADIANS(f))*dist)
                );
}
void GameEntity::forward(float dist, float angle)
{
    setRotation(getRotation()-angle);
    forward(dist);
}