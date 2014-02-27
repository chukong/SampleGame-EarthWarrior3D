//
//  ScrollingBackground.cpp
//  Moon3d
//
//  Created by Hao Wu on 2/24/14.
//
//

#include "ScrollingBackground.h"

USING_NS_CC;

bool ScrollBack::init()
{
    //xScroll = 0;
    spr = Sprite::create("groundLevel.jpg");
    this->addChild(spr);
    //spr->setTextureRect(Rect(0,512,512,1024));
    CCTexture2D::TexParams texRepeat = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    spr->getTexture()->setTexParameters(texRepeat);
    setRotation3D(Vertex3F(-30.0,0.0f,0.0f));
    spr->setScale(1.4);
    spr->setFlippedY(true);
    spr->setPosition(0.0f,400);
    

    
    

    //player = Sprite3D::create("Scania4.obj", "car00.png");
    player = Sprite3D::create("DownNecker.obj", "Done1.png");
    player->setScale(20);
    player->setPosition3D(Vertex3F(0,0,0));

    addChild(player,10);
    
    
    scheduleUpdate();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(ScrollBack::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ScrollBack::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ScrollBack::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, player);
    return true;
}

bool ScrollBack::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{

    return true;
}
void ScrollBack::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point prev = event->getCurrentTarget()->getPosition();
    event->getCurrentTarget()->setPosition(touch->getDelta()+prev);
}
void ScrollBack::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    log("end");
}

void ScrollBack::update(float dt){
    xScroll -= speed*dt;
    spr->setTextureRect(Rect(0,xScroll,512,1200));
    
    player->setRotation3D(Vertex3F(90,xScroll,180));
}
