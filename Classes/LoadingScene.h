//
//  LoadingScene.h
//  Moon3d
//
//  Created by cocos01 on 3/10/14.
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

#define TOTAL_PIC_NUM 20

class LoadingScene : public Layer
{
public:
    
    LoadingScene():currentNum(0),totalNum(TOTAL_PIC_NUM){};
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
    
    void LoadingCallback(Ref* pObj);
    void GotoNextScene(Ref* pObj);
    
private:
    int currentNum;
    int totalNum;
    
    ControlSlider* m_pSlider;
    LabelBMFont* m_pPercent;
    
};



#endif /* defined(__Moon3d__LoadingScene__) */
