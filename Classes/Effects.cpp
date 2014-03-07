//
//  Effects.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/6/14.
//
//

#include "Effects.h"

Vector<Node*> EffectPool::pool;

bool ExplosionFX::init(){
    _part1 = ParticleSystemQuad::create("toonSmoke.plist");
    _part2 = ParticleSystemQuad::create("flare.plist");
    addChild(_part1);
    addChild(_part2);
    _part1->setAutoRemoveOnFinish(true);
    _part2->setAutoRemoveOnFinish(true);
    setRotation3D(Vertex3F(30,0,0));
    return (_part1 && _part2);
}