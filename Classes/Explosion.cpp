//
//  Explosion.cpp
//  Moon3d
//
//  Created by Rye on 14-3-10.
//
//

#include "Explosion.h"
#include "Effects.h"

USING_NS_CC;

bool SmallExplosion::init(){
    part1 = ParticleSystemQuad::create("toonSmoke.plist");
    this->addChild(part1);
    part2 = ParticleSystemQuad::create("flare.plist");
    this->addChild(part2);
    part1->setTotalParticles(10);
    part1->setEmissionRate(9999999999);
    part2->setTotalParticles(3);
    part2->setEmissionRate(9999999999);
    part1->setRotation3D(Vertex3F(30,0,0));
    part2->setRotation3D(Vertex3F(30,0,0));
    return true;
}

void SmallExplosion::createExplosion(Node* _effectLayer, Point pos){
    
    part1->setTotalParticles(8);
    part1->setEmissionRate(9999999999);
    part1->setScale(0.7);
    part2->setTotalParticles(5);
    part2->setEmissionRate(9999999999);
    _effectLayer->addChild(this,7);
    part1->setRotation3D(Vertex3F(30,0,0));
    part2->setRotation3D(Vertex3F(30,0,0));
    this->setPosition(pos);
    this->scheduleOnce(schedule_selector(SmallExplosion::recycle), 1.5);
}

void SmallExplosion::recycle(float dt){
    this->removeFromParentAndCleanup(false);
    EffectManager::_smallExplPool.pushBack(this);
}

bool BigExplosion::init(){
    part1 = ParticleSystemQuad::create("toonSmoke.plist");
    this->addChild(part1);
    part2 = ParticleSystemQuad::create("glow.plist");
    this->addChild(part2);
    part3 = ParticleSystemQuad::create("debris.plist");
    this->addChild(part3);
    part1->setTotalParticles(10);
    part1->setEmissionRate(9999999999);
    part2->setTotalParticles(3);
    part2->setEmissionRate(9999999999);
    part3->setTotalParticles(20);
    part3->setEmissionRate(9999999999);
    part3->setScale(1.5);
    part1->setRotation3D(Vertex3F(30,0,0));
    part2->setRotation3D(Vertex3F(30,0,0));
    part3->setRotation3D(Vertex3F(30,0,0));
    return true;
}

void BigExplosion::createExplosion(Node *_effectLayer, Point pos){

    _effectLayer->addChild(this,6);
    part1->resetSystem();
    part2->resetSystem();
    part3->resetSystem();
    setPosition(pos);

    this->scheduleOnce(schedule_selector(BigExplosion::recycle), 1.2);
}

void BigExplosion::recycle(float dt){
    this->removeFromParentAndCleanup(false);
    EffectManager::_bigExplPool.pushBack(this);
}