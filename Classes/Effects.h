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
#include "Explosion.h"
USING_NS_CC;
USING_NS_CC_MATH;

class EffectManager
{
public:
    static void createExplosion(math::Vector2 pos);
    static void createBigExplosion(math::Vector2 pos);
    static void setLayer(Node* layer);
    static Vector<SmallExplosion*> _smallExplPool;
    static Vector<BigExplosion*> _bigExplPool;
protected:
    static Node* _effectLayer;

};


#endif /* defined(__Moon3d__Effects__) */
