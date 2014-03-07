#include "EnemyManager.h"
#include "Fodder.h"
#include "AirCraft.h"

using namespace cocos2d;
using namespace std;
//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
EnemyManager* EnemyManager::m_mySingleton = NULL;

EnemyManager::EnemyManager()
{
    
}

EnemyManager* EnemyManager::sharedEnemyManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new EnemyManager();
        m_mySingleton->addFodderToMemory();
    }
    //Return the singleton object
    return m_mySingleton;
}

void EnemyManager::addFodderToMemory()
{
    for (int i = 0; i<prepareFodderNum; i++)
    {
        Fodder * enemy = Fodder::create();
        enemy->retain();
        standByEnemyVect.pushBack(enemy);
    }
}

