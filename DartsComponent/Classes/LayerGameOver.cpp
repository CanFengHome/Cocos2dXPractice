//
//  LayerGameOver.cpp
//  Darts
//
//  Created by mfp on 15/11/27.
//
//

#include "LayerGameOver.h"


#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

#include "SceneWelcome.h"

SceneGameOver* SceneGameOver::createWithScore(bool isWin,int score)
{
    SceneGameOver *pRet = new(std::nothrow) SceneGameOver();
    if (pRet && pRet->initWithScore(isWin, score))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool SceneGameOver::initWithScore(bool isWin,int score)
{
    LayerGameOver* pGameLyr = LayerGameOver::createWithScore(isWin, score);
    addChild(pGameLyr);
    
    return true;
}

LayerGameOver* LayerGameOver::createWithScore(bool isWin,int score)
{
    LayerGameOver *pObj = new (std::nothrow) LayerGameOver();
    if (pObj && pObj->initWithScore(isWin,score))
    {
        pObj->autorelease();
        return pObj;
    }
    CC_SAFE_DELETE(pObj);
    return nullptr;
}

bool LayerGameOver::initWithScore(bool isWin,int score)
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();

    Label* pStatus = Label::createWithTTF("", "fonts/black.ttf", 50);
    if (isWin)
    {
        pStatus->setString("Win!");
    }
    else
    {
        pStatus->setString(__String::createWithFormat("Fail! Score:%d",score)->getCString());
    }
    
    pStatus->setPosition(winSize.width*0.5f,winSize.height*0.5f);
    pStatus->setColor(Color3B::BLACK);
    addChild(pStatus);
    
    Button* pBtnStart = Button::create();
    pBtnStart->setPressedActionEnabled(true);
    pBtnStart->addClickEventListener(CC_CALLBACK_1(LayerGameOver::btnBackCallback, this));
    pBtnStart->setTitleText("Back");
    pBtnStart->setTitleFontSize(28.0f);
    pBtnStart->setPosition(Vec2(pStatus->getPositionX(),pStatus->getPositionY()-pStatus->getContentSize().height));
    pBtnStart->setTitleColor(Color3B::BLACK);
    addChild(pBtnStart);
    
    return true;
}

void LayerGameOver::btnBackCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(SceneWelcome::create());
}












