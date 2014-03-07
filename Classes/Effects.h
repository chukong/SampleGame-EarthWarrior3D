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

class EffectManager
{
public:
    static void createExplosion(Point pos);
    static void setLayer(Node* layer);
protected:
    static Node* _effectLayer;
};


#endif /* defined(__Moon3d__Effects__) */
