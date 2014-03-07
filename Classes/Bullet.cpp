//
//  Bullet.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "Bullet.h"
#include "3d/Sprite3D.h"
#include "consts.h"
#include "GameLayer.h"
#include "GameEntity.h"
#include "EnemyManager.h"
#include "Fodder.h"

bool Bullet::init()
{
    _Model = Sprite::create("CloseSelected.png");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerBullet;
        return true;
    }
    return false;
}
bool PlayerBullet::init()
{
    _Model = Sprite::create("bullets.png", Rect(54, 57, 36, 67));
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerBullet;
        return true;
    }
    return false;
}

void Bullet::setVector(Point vec)
{
    _vector = vec;
}

Point Bullet::getVector()
{
    return _vector;
}
void Bullet::reset()
{
    setRotation(0);
}

bool Missile::init()
{
    _Model = Sprite3D::create("daodanv001.obj", "daodan_512.png");
    if(_Model)
    {
        addChild(_Model);
        _radius=10;
        _type = kPlayerMissiles;
        _Model->setScale(3);
        _Model->setRotation3D(Vertex3F(90,0,0));
        static_cast<Sprite3D*>(_Model)->setOutline(0.3, Color3B(0,0,0));
        
        _left = (CCRANDOM_MINUS1_1()>0);
        if(_left)
            _yRotSpeed *= -1;
        
        
        // missile effects

        
        auto part2 = ParticleSystemQuad::create("emission.plist");
        addChild(part2);
        part2->setPosition(0,-34);
        part2->setPositionType(tPositionType::GROUPED);
        //part2->setScale(2.5);
        auto part1 = ParticleSystemQuad::create("missileFlare.plist");
        addChild(part1);
        part1->setPosition(0,-30);
        part1->setPositionType(tPositionType::GROUPED);
        part1->setScale(2.5);
        return true;
    }
    return false;
}

void Missile::update(float dt)
{
    if(!_target)
    {
        //TODO: simplify this process
//        EnemyManager * aEnemyManager = EnemyManager::sharedEnemyManager();
//        std::vector<int> avilabelVect = aEnemyManager->getAllAvilabelFodder();
//        //get from random
//        int randid = CCRANDOM_0_1()*avilabelVect.size();
//        int randid2 = avilabelVect.at(randid);
//        auto t = static_cast<GameEntity*>(aEnemyManager->fodderVect.at(randid2));
//        if(t)
//        setTarget(static_cast<GameEntity*>(aEnemyManager->fodderVect.at(randid2)));
        setTarget(static_cast<GameLayer*>(getParent())->_testDummy);//very hacky
    }
    if(_target){
        //turn towards the target
        float angle = -CC_RADIANS_TO_DEGREES((getPosition() - _target->getPosition()).getAngle());
        float curRot = getRotation();
        float angleDif = std::min(std::max(angle-90 - curRot, -_turnRate*dt), _turnRate*dt);
        
        float f = curRot + angleDif;
        setRotation(f);
        setPosition(getPosition()+Point(sinf(CC_DEGREES_TO_RADIANS(f))*_velocity,cosf(CC_DEGREES_TO_RADIANS(f))*_velocity) + _vector*dt);
        _vector = _vector * (1-dt);
        
    }
    // missiles need to rotate
    _yRotation += _yRotSpeed*dt;
    _Model->setRotation3D(Vertex3F(90,_yRotation, 0));
    
    _velocity += _accel*dt;
}

void Missile::reset()
{
    setTarget(nullptr);
    _velocity = 0;
}

