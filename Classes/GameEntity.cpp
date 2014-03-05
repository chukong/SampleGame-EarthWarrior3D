//
//  GameEntity.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "GameEntity.h"

Node *GameEntity::getModel(){
    return _Model;
}

Vertex3F GameEntity::getOrientation(){
    return _orientation;
}