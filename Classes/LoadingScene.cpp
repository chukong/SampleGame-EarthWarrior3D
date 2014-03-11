//
//  LoadingScene.cpp
//  Moon3d
//
//  Created by Jacky on 3/10/14.
//
//

#include "LoadingScene.h"
#include "HelloWorldScene.h"

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize(); 

//	//LabelPercent
//	m_pLabelPercent = LabelTTF::create("0%","Arial",20);
//	m_pLabelPercent->setPosition(Point(visibleSize.width/2+35,visibleSize.height/2+30));  
//	this->addChild(m_pLabelPercent,2);  
//
//	//ProgressPercent
//	auto loadBg = Sprite::create("sliderTrack.png"); 
//	loadBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));  
//	this->addChild(loadBg,1);  
//
//	m_pLoadProgress = ProgressTimer::create(Sprite::create("sliderProgress.png"));
//	m_pLoadProgress->setBarChangeRate(Point(1,0));
//	m_pLoadProgress->setType(ProgressTimer::Type::BAR);
//	m_pLoadProgress->setMidpoint(Point(0,1));  
//	m_pLoadProgress->setPosition(Point(visibleSize.width/2,visibleSize.height/2));  
//	m_pLoadProgress->setPercentage(0.0f);
//	this->addChild(m_pLoadProgress,2);

    LoadingResource();
    
    return true;
}

void LoadingScene::LoadingResource()
{
    //Loading Music
    LoadingMusic();
    
    //Loading Picture
    LoadingPic();
}

void LoadingScene::LoadingMusic()
{
    auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
    Audio->preloadEffect("explodeEffect.mp3");
    Audio->preloadEffect("hit.mp3");
    Audio->preloadEffect("boom2.mp3");
    // Music By Matthew Pable (http://www.matthewpablo.com/)
    // Licensed under CC-BY 3.0 (http://creativecommons.org/licenses/by/3.0/)
    Audio->playBackgroundMusic("Flux.mp3");
}

void LoadingScene::LoadingPic()
{
	auto TexureCache=Director::getInstance()->getTextureCache();
    TexureCache->addImageAsync("groundLevel.jpg", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("bullets.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("car00.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("CloseNormal.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("CloseSelected.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("cloud.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("coco.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("daodan_32.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("daodan_512.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("diji02_v002_128.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("diji02_v002_1024.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("dijiyuanv001.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("Done1.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("fighter.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("fog.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("HelloWorld.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("leftTop.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("playerv002_256.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("playerv002_1024.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("rightTop.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
	TexureCache->addImageAsync("streak.png", CC_CALLBACK_1(LoadingScene::LoadingCallback, this));
}

void LoadingScene::LoadingCallback(Ref* pObj)
{
    ++currentNum;
    char tmp[10];
	int percent=(int)(((float)currentNum / totalNum) * 100);
    sprintf(tmp, "loading...%d%%", percent);
    CCLog(tmp);
    
//    m_pLabelPercent->setString(tmp);
//	m_pLoadProgress->setPercentage(percent);

    if (currentNum == totalNum)
    {
		this->removeAllChildren();
        
		//goto next scene.
        auto helloworldScene=HelloWorld::createScene();
        Director::getInstance()->replaceScene(helloworldScene);
    }
}

