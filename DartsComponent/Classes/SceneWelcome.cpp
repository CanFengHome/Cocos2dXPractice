//
//  SceneWelcome.cpp
//  Darts
//
//  Created by mfp on 15/11/26.
//
//

#include "SceneWelcome.h"

#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

#include "MacrosAssert.h"
#include "SceneMainGame.h"

#pragma mark LayerWelcome

bool LayerWelcome::init()
{
    if (!LayerColor::initWithColor(Color4B::GRAY))
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    float offsetY = 20.0f;
    
    Button* pBtnStart = Button::create();
    pBtnStart->setPressedActionEnabled(true);
    pBtnStart->addClickEventListener(CC_CALLBACK_1(LayerWelcome::btnStartGameCallback, this));
    pBtnStart->setTitleText("Start Game");
    pBtnStart->setTitleFontSize(28.0f);
    pBtnStart->setPosition(Vec2(winSize.width*0.5f,winSize.height*0.5f + offsetY));
    pBtnStart->setTitleColor(Color3B::BLACK);
    addChild(pBtnStart);

    Button* pBtnExit = Button::create();
    pBtnExit->setPressedActionEnabled(true);
    pBtnExit->addClickEventListener(CC_CALLBACK_1(LayerWelcome::btnEndGameCallback, this));
    pBtnExit->setTitleText("Exit Game");
    pBtnExit->setTitleFontSize(28.0f);
    pBtnExit->setPosition(Vec2(winSize.width*0.5f,winSize.height*0.5f - offsetY));
    pBtnExit->setTitleColor(Color3B::BLACK);
    addChild(pBtnExit);
    
    return true;
}

void LayerWelcome::btnStartGameCallback(cocos2d::Ref* pSender)
{
    SceneMainGame* pMainScene = SceneMainGame::create();
    Director::getInstance()->replaceScene(pMainScene);
}

void LayerWelcome::btnEndGameCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

#pragma mark SceneWelcome

bool SceneWelcome::init()
{
    addChild(LayerWelcome::create());
    
    return true;
}













