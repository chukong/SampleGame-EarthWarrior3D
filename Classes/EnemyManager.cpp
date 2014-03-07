#include "EnemyManager.h"
#include "Fodder.h"

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
        fodderVect.push_back(enemy);
        fodderAvilabelStateVect.push_back(i+1);
    }
}

vector<int> EnemyManager::getAllAvilabelFodder()
{
    vector<int> avilabelVect;
    
    for (int i = 0; i<fodderAvilabelStateVect.size(); i++)
    {
        if (fodderAvilabelStateVect[i]>0)
        {
            //log("333===%d",fodderAvilabelStateVect[i]);
            avilabelVect.push_back(fodderAvilabelStateVect[i]);
        }
    }
    
    return avilabelVect;
}