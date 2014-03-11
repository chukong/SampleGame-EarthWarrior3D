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

    // add layer as a child to scene
    scene->addChild(layer);

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
    
    //TODO: replace with real ui
    auto lefttopUI = Sprite::create("leftTop.png");
    lefttopUI->setAnchorPoint(Point(0,1));
    lefttopUI->setPosition(Point(0, visibleSize.height+origin.y));
    addChild(lefttopUI);
    
    auto rightTopUI = Sprite::create("rightTop.png");
    rightTopUI->setAnchorPoint(Point(1,1));
    rightTopUI->setPosition(origin+Point(visibleSize));
    addChild(rightTopUI);
    
    // Easter Egg
//    auto cocos = Sprite3D::create("coconut.obj", "coco.png");
//    auto coco = cocos;
//    addChild(coco);
//    coco->setScale(1);
//    coco->setOutline(10, Color3B(0,0,0));
//    coco->setPosition(320,480);
//    coco->runAction(RepeatForever::create(RotateBy::create(0.3, Vertex3F(10,12,13))));
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
