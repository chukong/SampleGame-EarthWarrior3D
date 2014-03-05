//
//  BulletController.h
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#ifndef __Moon3d__BulletController__
#define __Moon3d__BulletController__

#include "cocos2d.h"
USING_NS_CC;
class Bullet;

class BulletController
{
public:
    static void reset();
    static bool init(Node *bulletLayer);
    static void spawnBullet(int type, Point pos, Point vec);
    static void update(float dt);
    static Vector<Bullet*> bullets;

protected:
        //static BulletController *s_instance;
    static bool _inited;
    static Node *_bulletLayer;
};

#endif /* defined(__Moon3d__BulletController__) */
