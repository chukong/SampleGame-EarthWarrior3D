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
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define TOTAL_PIC_NUM 21

class LoadingScene : public Layer
{
public:
    
    LoadingScene():currentNum(0),totalNum(TOTAL_PIC_NUM){};
    
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(LoadingScene);
    
private:
    
    void LoadingResource();
    void LoadingMusic();
    void LoadingPic();
    
    void LoadingCallback(Ref* pObj);
    
private:
    int currentNum;
    int totalNum;

	ProgressTimer* m_pLoadProgress;  
	LabelTTF* m_pLabelPercent;
    
};



#endif /* defined(__Moon3d__LoadingScene__) */
