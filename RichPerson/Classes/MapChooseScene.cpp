//
//  MapChooseScene.cpp
//  RichPerson
//
//  Created by mfp on 16/5/11.
//
//

#include "MapChooseScene.h"
#include "MenuScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

#pragma mark MapChooseScene

bool MapChooseScene::init()
{
    MapChooseLayer* pMapChooseLayer = MapChooseLayer::create();
    addChild(pMapChooseLayer);
    
    return true;
}


#pragma mark MapChooseLayer

bool MapChooseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    // bg sprite
    Sprite* pBgSprite = Sprite::create("res/map/stage_background.png");
    pBgSprite->setPosition(winSize*0.5f);
    addChild(pBgSprite);
    
    // back button
    Button* pGoBackBtn = Button::create("res/images/back_normal.png","res/mages/back_pressed.png");
    pGoBackBtn->setPressedActionEnabled(true);
    pBgSprite->addChild(pGoBackBtn);
    Size btnBackSize = pGoBackBtn->getContentSize();
    pGoBackBtn->addTouchEventListener(CC_CALLBACK_2(MapChooseLayer::btnGoBackCallback, this));
    pGoBackBtn->setPosition(Vec2(winSize.width - btnBackSize.width, btnBackSize.height*0.6f));
    
    // page view
    m_pPageView = PageView::create();
    m_pPageView->setContentSize(Size(winSize.width, 300.0f));
    m_pPageView->setPosition(Vec2(0.0f, 100.0f));
    m_pPageView->setBounceEnabled(true);
    pBgSprite->addChild(m_pPageView);
    
    m_pPageView->removeAllPages();
    int pageCount = 3;
    for (int i = 0; i < pageCount; ++i)
    {
        Layout* pLayout = Layout::create();
        pLayout->setContentSize(Size(winSize.width, 300.0f));
        
        std::string strMapImg(__String::createWithFormat("res/map/map_%d.png", i+1)->getCString());
        Button* pBtnMap = Button::create(strMapImg, strMapImg);
        pBtnMap->setPressedActionEnabled(true);
        pBtnMap->addTouchEventListener(CC_CALLBACK_2(MapChooseLayer::btnMapCallback, this));
        pLayout->addChild(pBtnMap);
        pBtnMap->setPosition(pLayout->getContentSize()*0.5f);
        
        m_pPageView->insertPage(pLayout,i);
    }
    
    return true;
}

void MapChooseLayer::btnGoBackCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->replaceScene(MenuScene::create());
    }
}

void MapChooseLayer::btnMapCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        if (m_pPageView == nullptr)
        {
            return;
        }
        
        ssize_t currPageIndex = m_pPageView->getCurrentPageIndex();
        log("current page index: %ld", currPageIndex);
    }
}




















