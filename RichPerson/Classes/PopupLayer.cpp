//
//  PopupLayer.cpp
//  RichPerson
//
//  Created by mfp on 16/5/11.
//
//

#include "PopupLayer.h"
#include "CommonDefine.h"

USING_NS_CC;
using namespace cocos2d::ui;

PopupLayer* PopupLayer::createMsgWindow(const std::string& msgTitle, const std::string& msgContent)
{
    PopupLayer *pRet = new(std::nothrow) PopupLayer();
    if (pRet && pRet->initWithTitleAndContent(msgTitle, msgContent))
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

bool PopupLayer::initWithTitleAndContent(const std::string& msgTitle, const std::string& msgContent)
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 128)))
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* pBgSprite = Sprite::create("res/popup_layer/dialog_bg.png");
    addChild(pBgSprite);
    pBgSprite->setPosition(winSize*0.5f);
    
    float midWidth = pBgSprite->getContentSize().width*0.5f;
    float height = pBgSprite->getContentSize().height;
    
    // lbl title
    Label* pLblTitle = Label::createWithTTF(msgTitle, FONT_TTF_PATH, 24.0f);
    pLblTitle->setPosition(midWidth, height-20.0f);
    pLblTitle->setTextColor(Color4B::BLACK);
    pBgSprite->addChild(pLblTitle);
    
    // lbl content
    Label* pLblContent = Label::createWithTTF(msgContent, FONT_TTF_PATH, 24.0f);
    pLblContent->setPosition(midWidth, height*0.5f);
    pLblContent->setTextColor(Color4B::BLACK);
    pBgSprite->addChild(pLblContent);
    
    // button ok and cancel
    Button* pBtnOk = Button::create("res/popup_layer/button_bg1.png", "res/popup_layer/button_bg1.png");
    float btnWidth = pBtnOk->getContentSize().width;
    float btnHeight = pBtnOk->getContentSize().height;
    
    pBtnOk->setPressedActionEnabled(true);
    pBtnOk->setTitleFontSize(20);
    pBgSprite->addChild(pBtnOk);
    pBtnOk->addTouchEventListener(CC_CALLBACK_2(PopupLayer::btnOkCallback, this));
    pBtnOk->setPosition(Vec2(midWidth-btnWidth, btnHeight));
    pBtnOk->setTitleText("确定");
    
    Button* pBtnCancel = Button::create("res/popup_layer/button_bg3.png", "res/popup_layer/button_bg3.png");
    pBtnCancel->setPressedActionEnabled(true);
    pBtnCancel->setTitleFontSize(20);
    pBgSprite->addChild(pBtnCancel);
    pBtnCancel->addTouchEventListener(CC_CALLBACK_2(PopupLayer::btnOkCallback, this));
    pBtnCancel->addTouchEventListener(CC_CALLBACK_2(PopupLayer::btnCancelCallback, this));
    pBtnCancel->setPosition(Vec2(midWidth+btnWidth, btnHeight));
    pBtnCancel->setTitleText("取消");

    pBgSprite->setScale(0.0f);
    pBgSprite->runAction(ScaleTo::create(0.3f, 1.0f));
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *t, Event *e)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void PopupLayer::setOkEventListener(const PopupLayerButtonCallback& okCallback)
{
    this->m_clickOkEventListener = okCallback;
}

void PopupLayer::PopupLayer::setCancelEventListener(const PopupLayerButtonCallback& cancelCallback)
{
    this->m_clickCancelEventListener = cancelCallback;
}

void PopupLayer::btnOkCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        if (m_clickOkEventListener)
        {
            m_clickOkEventListener();
        }
        
        Director::getInstance()->getRunningScene()->removeChild(this);
    }
}

void PopupLayer::btnCancelCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        if (m_clickCancelEventListener)
        {
            m_clickCancelEventListener();
        }
        
        Director::getInstance()->getRunningScene()->removeChild(this);
    }
}

void PopupLayer::showPopupLayer(PopupLayer* popupLyr)
{
    if (popupLyr == nullptr)
    {
        return;
    }
    
    Director::getInstance()->getRunningScene()->addChild(popupLyr);
}




















