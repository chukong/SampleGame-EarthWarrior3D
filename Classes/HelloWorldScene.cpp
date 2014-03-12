#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "3d/Sprite3D.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->setTag(100);
    // add layer as a child to scene
    scene->addChild(layer);

    // add warning layer
    auto warningLayer = LayerColor::create(Color4B(255, 0, 0, 60));
    warningLayer->setOpacity(0);
    warningLayer->setTag(456);
    scene->addChild(warningLayer);
    
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto sb = GameLayer::create();
    sb->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(sb);
    auto fog = Sprite::create("fog.png");
    addChild(fog);
    fog->setPosition(visibleSize.width/2,visibleSize.height/2+285);
    fog->setScaleX(visibleSize.width/10);
    
    //HP
    auto lefttopUI = Sprite::create("hp_empty.png");
    lefttopUI->setAnchorPoint(Point(0,1));
    lefttopUI->setPosition(Point(0, visibleSize.height+origin.y));
    addChild(lefttopUI);
    
    hpView = ProgressTimer::create(Sprite::create("hp.png"));
    hpView->setType(ProgressTimer::Type::BAR);
    hpView->setMidpoint(Point(0,0));
    hpView->setPercentage(1);
    hpView->setBarChangeRate(Point(0, 1));
    hpView->setPercentage(100);
    hpView->setAnchorPoint(Point(0,1));
    hpView->setPosition(Point(16, visibleSize.height+origin.y-31));
    addChild(hpView);
    
    
    //Score
    auto rightTopUI = Sprite::create("right_top_ui.png");
    rightTopUI->setAnchorPoint(Point(1,1));
    rightTopUI->setPosition(origin+Point(visibleSize));
    this->addChild(rightTopUI);
    
    //the menuitem to show score
    scoreLabel = LabelAtlas::create("0", "score_right_top.png", 23, 28, '0');
    scoreLabel->setAnchorPoint(Point(1,0.5));
    scoreLabel->setPosition(visibleSize.width-40,visibleSize.height-45);
    this->addChild(scoreLabel);

    this->schedule(schedule_selector(HelloWorld::increaseScore), (float)1/10);
    //this->addChild(scoreLabel);

    
    // Easter Egg
//    auto cocos = Sprite3D::create("coconut.obj", "coco.png");
//    auto coco = cocos;
//    addChild(coco);
//    coco->setScale(1);
//    coco->setOutline(10, Color3B(0,0,0));
//    coco->setPosition(320,480);
//    coco->runAction(RepeatForever::create(RotateBy::create(0.3, Vertex3F(10,12,13))));
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    return true;
}

void HelloWorld::increaseScore(float dt){
    this->score++;
    std::stringstream ss;
    std::string str;
    ss<<score;
    ss>>str;
    const char *p = str.c_str();
    scoreLabel->setString(p);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
