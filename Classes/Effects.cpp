//
//  Effects.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/6/14.
//
//

#include "Effects.h"

Node* EffectManager::_effectLayer = nullptr;

void EffectManager::createExplosion(Point pos)
{
    if(!_effectLayer)
    {
        return;
    }
    auto part1 = ParticleSystemQuad::create("toonSmoke.plist");
    auto part2 = ParticleSystemQuad::create("flare.plist");
    _effectLayer->addChild(part1);
    _effectLayer->addChild(part2);
    part1->setAutoRemoveOnFinish(true);
    part2->setAutoRemoveOnFinish(true);
    part1->setRotation3D(Vertex3F(30,0,0));
    part2->setRotation3D(Vertex3F(30,0,0));
    part1->setPosition(pos);
    part2->setPosition(pos);
}

void EffectManager::setLayer(Node *layer)
{
    _effectLayer = layer;
}