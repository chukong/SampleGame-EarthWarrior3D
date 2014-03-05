//
//  BulletController.cpp
//  Moon3d
//
//  Created by Hao Wu on 3/4/14.
//
//

#include "BulletController.h"

BulletController* BulletController::getInstance()
{
    if (!s_instance)
    {
        s_instance = new BulletController();
        s_instance->init();
    }
    
    return s_instance;
}
BulletController::BulletController()
{
    
}
bool BulletController::init()
{
    return true;
}
void BulletController::resetInstance()
{
    
}
BulletController* BulletController::s_instance = nullptr;