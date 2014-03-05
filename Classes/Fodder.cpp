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
    _Model = Sprite3D::create("diji1_v001.obj", "diji02_v002_1024.png");
    if(_Model)
    {
        _Model->setScale(10);
        addChild(_Model);
        _Model->setRotation3D(Vertex3F(90,0,0));
                static_cast<Sprite3D*>(_Model)->setOutline(5.0, Color3B(0,0,0));
        _radius=40;
        return true;
    }
    return false;
}