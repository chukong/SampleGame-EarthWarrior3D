//
//  LoadingScene.h
//  Moon3d
//
//  Created by Jacky on 3/10/14.
//
//

#ifndef __Moon3d__LoadingScene__
#define __Moon3d__LoadingScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

#define TOTAL_PIC_NUM 11

#define PRELOAD_FODDER_COUNT 18
#define PRELOAD_FODDERL_COUNT 3
#define PRELOAD_BIGDUDE_COUBR 5
#define PRELOAD_MISSILE_COUNT 5

class LoadingScene : public Layer
{
public:
    
    LoadingScene():currentNum(0),
    totalNum(TOTAL_PIC_NUM),
    m_curPreload_fodder_count(0),
    m_curPreload_fodderL_count(0),
    m_curPreload_BigDude_count(0),
    m_curPreload_Missile_count(0){};
    
    ~LoadingScene();
    
    static Scene* createScene();
    
    virtual bool init();
    
    void update(float dt);
    
    CREATE_FUNC(LoadingScene);
    
private:
    void InitBk();
    void InitCoco();
    void LoadingResource();
    void LoadingMusic();
    void LoadingPic();
    void LoadingEnemy(int type);
    void LoadingBullet(int type);
    
    void LoadingCallback(Ref* pObj);
    void GotoNextScene(Ref* pObj);
    void RunNextScene();
    
    
private:
    int currentNum;
    int totalNum;
    
    ControlSlider* m_pSlider;
    LabelBMFont* m_pPercent;
    
    int m_curPreload_fodder_count;
    int m_curPreload_fodderL_count;
    int m_curPreload_BigDude_count;
    int m_curPreload_Missile_count;
    
    static int updatecount;
    
};



#endif /* defined(__Moon3d__LoadingScene__) */
