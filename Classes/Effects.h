//
//  Effects.h
//  Moon3d
//
//  Created by Hao Wu on 3/6/14.
//
//

#ifndef __Moon3d__Effects__
#define __Moon3d__Effects__

#include "cocos2d.h"
USING_NS_CC;

class EffectPool
{
public:
    static Vector<Node*> pool;
};

class ExplosionFX : public Node
{
public:
    CREATE_FUNC(ExplosionFX);
    bool init();
protected:
    ParticleSystemQuad* _part1;
    ParticleSystemQuad* _part2;
};


#endif /* defined(__Moon3d__Effects__) */
