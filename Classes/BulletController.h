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
class Bullet;

class BulletController
{
public:
    static BulletController *getInstance();

protected:
    std::vector<Bullet*> bullets;
    static BulletController *s_instance;
    bool init();
    BulletController();
};

#endif /* defined(__Moon3d__BulletController__) */
