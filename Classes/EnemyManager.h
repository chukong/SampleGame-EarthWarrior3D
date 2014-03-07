//
//  PublicApi.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__EnemyManager__
#define __Moon3d__EnemyManager__

#include "cocos2d.h"
class Fodder;
class AirCraft;
class EnemyManager
{
private:
    //Constructor
    EnemyManager();
   
    int prepareFodderNum = 5;
    
    //Instance of the singleton
    static EnemyManager* m_mySingleton;
    void addFodderToMemory();
    
public:
    //Get instance of singleton
    cocos2d::Vector<AirCraft*> standByEnemyVect;
    cocos2d::Vector<AirCraft*> availabelEnemyVect;
    
    static EnemyManager* sharedEnemyManager();
};

#endif /* defined(__Moon3d__PublicApi__) */