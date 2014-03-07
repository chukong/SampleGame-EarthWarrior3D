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
    part1->setTotalParticles(8);
    part1->setEmissionRate(9999999999);
    part1->setScale(0.7);
    auto part2 = ParticleSystemQuad::create("flare.plist");
    part2->setTotalParticles(5);
    part2->setEmissionRate(9999999999);
    _effectLayer->addChild(part1);
    _effectLayer->addChild(part2);
    part1->setAutoRemoveOnFinish(true);
    part2->setAutoRemoveOnFinish(true);
    part1->setRotation3D(Vertex3F(30,0,0));
    part2->setRotation3D(Vertex3F(30,0,0));
    part1->setPosition(pos);
    part2->setPosition(pos);
}

void EffectManager::createBigExplosion(Point pos)
{
    if(!_effectLayer)
    {
        return;
    }
    auto part1 = ParticleSystemQuad::create("toonSmoke.plist");
    part1->setTotalParticles(10);
    part1->setEmissionRate(9999999999);
    auto part2 = ParticleSystemQuad::create("glow.plist");
    part2->setTotalParticles(3);
    part2->setEmissionRate(9999999999);
    auto part3 = ParticleSystemQuad::create("debris.plist");
    part3->setTotalParticles(20);
    part3->setEmissionRate(9999999999);
    part3->setScale(1.5);
    _effectLayer->addChild(part1);
    _effectLayer->addChild(part2);
    _effectLayer->addChild(part3);
    part1->setAutoRemoveOnFinish(true);
    part2->setAutoRemoveOnFinish(true);
    part3->setAutoRemoveOnFinish(true);
    part1->setRotation3D(Vertex3F(30,0,0));
    part2->setRotation3D(Vertex3F(30,0,0));
    part3->setRotation3D(Vertex3F(30,0,0));
    part1->setPosition(pos);
    part2->setPosition(pos);
    part3->setPosition(pos);
}

void EffectManager::setLayer(Node *layer)
{
    _effectLayer = layer;
}