//
//  MenuScene.cpp
//  RichPerson
//
//  Created by mfp on 16/5/10.
//
//

#include "MenuScene.h"
#include "CommonDefine.h"
#include "PopupLayer.h"
#include "MapChooseScene.h"

USING_NS_CC;
using namespace ui;

#pragma mark MenuScene

bool MenuScene::init()
{
    MenuLayer* pMenuLayer = MenuLayer::create();
    addChild(pMenuLayer);
    
    return true;
}



#pragma mark MenuLayer

bool MenuLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    float midScene = winSize.width*0.5f;
    
    Sprite* pLogoSprite= Sprite::create("res/menu/menuLogo.png");
    pLogoSprite->setPosition(midScene, winSize.height);
    pLogoSprite->setAnchorPoint(Vec2(0.5f, 1.0f));
    pLogoSprite->setScale(0.6f);
    addChild(pLogoSprite);
    
    Sprite* pRainBowSprite= Sprite::create("res/menu/rainbow.png");
    pRainBowSprite->setPosition(5.0f, winSize.height-20.0f);
    pRainBowSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    pRainBowSprite->setScale(0.3f);
    addChild(pRainBowSprite);
    
    MoveBy* rainBowMove = MoveBy::create(1, Vec2(8.0f, 0.0f));
    MoveBy* rainBowMoveReverse = rainBowMove->reverse();
    Sequence* rainBowAction = Sequence::create(rainBowMove, rainBowMoveReverse, nullptr);
    pRainBowSprite->runAction(RepeatForever::create(rainBowAction));
    
    float startHeight = winSize.height - 180.0f;
    float distance = 65.0f;
    // button Button *pBtnSiglePerson =
    createNewButton(CC_CALLBACK_2(MenuLayer::btnSiglePersonCallback, this),
                    Vec2(midScene, startHeight),"单击游戏");
    
    createNewButton(CC_CALLBACK_2(MenuLayer::btnMultiplePersonCallback, this),
                    Vec2(midScene, startHeight - distance),"多人游戏");
    
    Button* pBtnMusicOn = createNewButton(CC_CALLBACK_2(MenuLayer::btnSoundCallback, this),
                                          Vec2(midScene, startHeight - distance*2.0f),"开启音效");
    
    createNewButton(CC_CALLBACK_2(MenuLayer::btnLoadGameCallback, this),
                    Vec2(midScene, startHeight - distance*3.0f),"载入游戏");
    
    createNewButton(CC_CALLBACK_2(MenuLayer::btnExitGameCallback, this),
                    Vec2(midScene, startHeight - distance*4.0f),"退出游戏");
    
    bool bMusicOn = UserDefault::getInstance()->getBoolForKey(UD_KEY_MUSIC_ON, true);
    if (bMusicOn)
    {
        pBtnMusicOn->setTitleText("开启音效");
    }
    else
    {
        pBtnMusicOn->setTitleText("关闭音效");
    }
    
    return true;
}

Button* MenuLayer::createNewButton(const Widget::ccWidgetTouchCallback& callback, const Vec2& btnPosition, const std::string& strTitle)
{
    Button* pBtn = Button::create("res/menu/normal_menu.png","res/menu/press_menu.png");
    pBtn->setPressedActionEnabled(true);
    pBtn->setTitleFontSize(25);
    addChild(pBtn);
    
    pBtn->addTouchEventListener(callback);
    pBtn->setPosition(btnPosition);
    pBtn->setTitleText(strTitle);
    
    return pBtn;
}

void MenuLayer::btnSiglePersonCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->replaceScene(MapChooseScene::create());
    }
}

void MenuLayer::btnMultiplePersonCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        
    }
}

void MenuLayer::btnSoundCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        Button* pBtnMusicOn = dynamic_cast<Button*>(pSender);
        if (pBtnMusicOn == nullptr)
        {
            return;
        }
        
        bool bMusicOn = UserDefault::getInstance()->getBoolForKey(UD_KEY_MUSIC_ON, false);
        if (bMusicOn)
        {
            UserDefault::getInstance()->setBoolForKey(UD_KEY_MUSIC_ON, false);
            pBtnMusicOn->setTitleText("关闭音效");
        }
        else
        {
            UserDefault::getInstance()->setBoolForKey(UD_KEY_MUSIC_ON, true);
            pBtnMusicOn->setTitleText("开启音效");
        }
    }
}

void MenuLayer::btnLoadGameCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        
    }
}

void MenuLayer::btnExitGameCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        PopupLayer* pPopupLyr = PopupLayer::createMsgWindow("提示消息", "你要退出吗？");
        pPopupLyr->setOkEventListener(CC_CALLBACK_0(MenuLayer::btnOkCallbackInPopupLayer, this));
        PopupLayer::showPopupLayer(pPopupLyr);
    }
}

void MenuLayer::btnOkCallbackInPopupLayer()
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



















