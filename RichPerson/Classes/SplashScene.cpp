//
//  SplashScene.cpp
//  RichPerson
//
//  Created by mfp on 16/5/10.
//
//

#include "SplashScene.h"

USING_NS_CC;

#pragma mark SplashScene

bool SplashScene::init()
{
    SplashLayer* pSplashLayer = SplashLayer::create();
    addChild(pSplashLayer);
    
    return true;
}




#pragma mark SplashLayer

bool SplashLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    float midWidth = winSize.width*0.5f;
    float midHeight = winSize.height*0.5f;
    
    Sprite* pWengSprite = Sprite::create("res/splash/weng.png");
    float spriteWidth = pWengSprite->getContentSize().width;
    pWengSprite->setPosition(midWidth-spriteWidth*1.5f, midHeight);
    addChild(pWengSprite);
    
    Sprite* pFu2Sprite = Sprite::create("res/splash/fu2.png");
    pFu2Sprite->setPosition(midWidth-spriteWidth*0.5f, midHeight);
    addChild(pFu2Sprite);
    
    Sprite* pPoSprite = Sprite::create("res/splash/po.png");
    pPoSprite->setPosition(midWidth+spriteWidth*0.5f, midHeight);
    addChild(pPoSprite);
    
    Sprite* pFu1Sprite = Sprite::create("res/splash/fu1.png");
    pFu1Sprite->setPosition(midWidth+spriteWidth*1.5f,midHeight);
    addChild(pFu1Sprite);
    
    float delayTime = 0.2f;
    float unitTime = 0.8f;
    
    pFu1Sprite->runAction(Sequence::create(DelayTime::create(delayTime),
                                           MoveBy::create(unitTime*3.0f, Vec2(-spriteWidth*3.0f, 0.0f)),
                                           NULL));
    pPoSprite->runAction(Sequence::create(DelayTime::create(delayTime),
                                          MoveBy::create(unitTime, Vec2(spriteWidth, 0.0f)),
                                          NULL));
    pFu2Sprite->runAction(Sequence::create(DelayTime::create(delayTime*2.0f+unitTime),
                                           MoveBy::create(unitTime, Vec2(spriteWidth, 0.0f)),
                                           NULL));
    pWengSprite->runAction(Sequence::create(DelayTime::create(delayTime*3.0f+unitTime*2.0f),
                                            MoveBy::create(unitTime, Vec2(spriteWidth, 0.0f)),
                                            NULL));
    
    return true;
}





















