//
//  Fodder.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#include "Fodder.h"

bool Fodder::init()
{
    _Model = Sprite3D::create("fighter.obj", "fighter.png");
    if(_Model)
    {
        _Model->setScale(20);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
        _radius=40;
        return true;
    }
    return false;
}