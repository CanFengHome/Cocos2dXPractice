//
//  NavigateController.cpp
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#include "NavigateController.h"
#include "MacrosAssert.h"
#include "CommonDefine.h"
#include "UpdateViewController.h"
#include "TmxHelperController.h"
#include "TmxCollisionController.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

static const float FIXED_OFFSET_X = 32.0f;
static const float FIXED_OFFSET_Y = 32.0f;

bool NavigateController::init()
{
    _name = "NavigateController";
    return true;
}

void NavigateController::onAdd()
{
    CC_RETURN_IF_ASSERT_FAIL(_owner != nullptr && _owner->getParent() != nullptr);
    
    m_fOffsetX = 0.0f;
    m_fOffsetY = 0.0f;
    m_fElapsedTime = 0.0f;
    m_fMoveInternalTime = 0.5f;
    
    initNavigationButton();
    _owner->unscheduleUpdate();
}

void NavigateController::onEnter()
{
    Node* pLayerGame = _owner->getParent()->getChildByName(LAYER_GAME_NAME);
    CC_RETURN_IF_ASSERT_FAIL(pLayerGame != nullptr);
    
    Node* pNavigationTarget = pLayerGame->getChildByName(LAYER_GAME_NAME_NODE_PLAYER);
    CC_RETURN_IF_ASSERT_FAIL(pNavigationTarget != nullptr);
    
    Node* pTiledMap = pLayerGame->getChildByName(LAYER_GAME_NAME_NODE_MAP);
    CC_RETURN_IF_ASSERT_FAIL(pTiledMap != nullptr);
    
    TmxHelperController* pTmxHelperCtrl = dynamic_cast<TmxHelperController*>(pTiledMap->getComponent("TmxHelperController"));
    CC_RETURN_IF_ASSERT_FAIL(pTmxHelperCtrl != nullptr);
    
    m_BoundRect = Rect(pNavigationTarget->getContentSize().width*0.5f,
                       pNavigationTarget->getContentSize().height*0.5f,
                       pTmxHelperCtrl->getMapViewWidth() - pNavigationTarget->getContentSize().width*0.5f,
                       pTmxHelperCtrl->getMapViewHeight() - pNavigationTarget->getContentSize().height*0.5f);
    // update view
    UpdateViewController* pUpdateViewCtrl = dynamic_cast<UpdateViewController*>(pLayerGame->getComponent("UpdateViewController"));
    CC_RETURN_IF_ASSERT_FAIL(pUpdateViewCtrl != nullptr);
    pUpdateViewCtrl->updateView();
    _owner->unscheduleUpdate();
}

void NavigateController::initNavigationButton()
{
    Button* pBtnLeft = Button::create();
    pBtnLeft->setPressedActionEnabled(true);
    pBtnLeft->addTouchEventListener(CC_CALLBACK_2(NavigateController::btnDirectionLeftCallback, this));
    pBtnLeft->setTitleText("左");
    _owner->addChild(pBtnLeft);
    
    Button* pBtnDown = Button::create();
    pBtnDown->setPressedActionEnabled(true);
    pBtnDown->addTouchEventListener(CC_CALLBACK_2(NavigateController::btnDirectionDownCallback, this));
    pBtnDown->setTitleText("下");
    _owner->addChild(pBtnDown);
    
    Button* pBtnRight = Button::create();
    pBtnRight->setPressedActionEnabled(true);
    pBtnRight->addTouchEventListener(CC_CALLBACK_2(NavigateController::btnDirectionRightCallback, this));
    pBtnRight->setTitleText("右");
    _owner->addChild(pBtnRight);
    
    Button* pBtnUp = Button::create();
    pBtnUp->setPressedActionEnabled(true);
    pBtnUp->addTouchEventListener(CC_CALLBACK_2(NavigateController::btnDirectionUpCallback, this));
    pBtnUp->setTitleText("上");
    _owner->addChild(pBtnUp);
    
    pBtnLeft->setTitleFontSize(40.0f);
    pBtnLeft->setTitleColor(Color3B::BLACK);
    pBtnLeft->setPosition(Vec2(pBtnLeft->getContentSize().width*0.5f,pBtnLeft->getContentSize().height*1.5f));
    
    pBtnDown->setTitleFontSize(40.0f);
    pBtnDown->setTitleColor(Color3B::BLACK);
    pBtnDown->setPosition(Vec2(pBtnDown->getContentSize().width*1.5f,pBtnDown->getContentSize().height*0.5f));
    
    pBtnRight->setTitleFontSize(40.0f);
    pBtnRight->setTitleColor(Color3B::BLACK);
    pBtnRight->setPosition(Vec2(pBtnRight->getContentSize().width*2.5f,pBtnRight->getContentSize().height*1.5f));
    
    pBtnUp->setTitleFontSize(40.0f);
    pBtnUp->setTitleColor(Color3B::BLACK);
    pBtnUp->setPosition(Vec2(pBtnUp->getContentSize().width*1.5f,pBtnUp->getContentSize().height*2.5f));
}

void NavigateController::btnDirectionLeftCallback(cocos2d::Ref* pSender, Widget::TouchEventType pTouchEventType)
{
    m_fOffsetX = -FIXED_OFFSET_X;
    m_fOffsetY = 0.0f;
    
    clickButton(pTouchEventType);
}

void NavigateController::btnDirectionDownCallback(cocos2d::Ref* pSender, Widget::TouchEventType pTouchEventType)
{
    m_fOffsetX = 0.0f;
    m_fOffsetY = -FIXED_OFFSET_Y;
    
    clickButton(pTouchEventType);
}

void NavigateController::btnDirectionRightCallback(cocos2d::Ref* pSender, Widget::TouchEventType pTouchEventType)
{
    m_fOffsetX = FIXED_OFFSET_X;
    m_fOffsetY = 0.0f;
    
    clickButton(pTouchEventType);
}

void NavigateController::btnDirectionUpCallback(cocos2d::Ref* pSender, Widget::TouchEventType pTouchEventType)
{
    m_fOffsetX = 0.0f;
    m_fOffsetY = FIXED_OFFSET_Y;
    
    clickButton(pTouchEventType);
}

void NavigateController::clickButton(const cocos2d::ui::Widget::TouchEventType& pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::BEGAN)
    {
        startMove();
    }
    else if (pTouchEventType == Widget::TouchEventType::ENDED)
    {
        endMove();
    }
}

void NavigateController::startMove()
{
    m_fElapsedTime = m_fMoveInternalTime;
    _owner->scheduleUpdate();
}

void NavigateController::endMove()
{
    m_fOffsetX = 0.0f;
    m_fOffsetY = 0.0f;
    m_fElapsedTime = 0.0f;
    _owner->unscheduleUpdate();
}

void NavigateController::update(float delta)
{
    Node* pLayerGame = _owner->getParent()->getChildByName(LAYER_GAME_NAME);
    CC_RETURN_IF_ASSERT_FAIL(pLayerGame != nullptr);
    
    Node* pNavigationTarget = pLayerGame->getChildByName(LAYER_GAME_NAME_NODE_PLAYER);
    CC_RETURN_IF_ASSERT_FAIL(pNavigationTarget != nullptr);
    
    // update view
    UpdateViewController* pUpdateViewCtrl = dynamic_cast<UpdateViewController*>(pLayerGame->getComponent("UpdateViewController"));
    CC_RETURN_IF_ASSERT_FAIL(pUpdateViewCtrl != nullptr);
    pUpdateViewCtrl->updateView();
    
    Node* pTiledMap = pLayerGame->getChildByName(LAYER_GAME_NAME_NODE_MAP);
    CC_RETURN_IF_ASSERT_FAIL(pTiledMap != nullptr);

    TmxHelperController* pTmxHelperCtrl = dynamic_cast<TmxHelperController*>(pTiledMap->getComponent("TmxHelperController"));
    CC_RETURN_IF_ASSERT_FAIL(pTmxHelperCtrl != nullptr);
    
    // 保证在边界范围内
    if (m_BoundRect.containsPoint(pNavigationTarget->getPosition()))
    {
        m_fElapsedTime += delta;
        if (m_fElapsedTime < m_fMoveInternalTime)
        {
            return;
        }
        
        m_fElapsedTime -= m_fMoveInternalTime;
        TmxCollisionController* pTmxCollisiionCtrl = dynamic_cast<TmxCollisionController*>(pTiledMap->getComponent("TmxCollisionController"));
        CC_RETURN_IF_ASSERT_FAIL(pTmxCollisiionCtrl != nullptr);
        if (!pTmxCollisiionCtrl->isCollision(pNavigationTarget->getPosition()+Vec2(m_fOffsetX, m_fOffsetY)) &&
            pNavigationTarget->getNumberOfRunningActions() == 0) // 防止移动动画期间，连续单击了按钮
        {
//            CCLOG(" curr %f,%f   offset %f,%f", pNavigationTarget->getPositionX(), pNavigationTarget->getPositionY(), m_fOffsetX, m_fOffsetY);
            pNavigationTarget->runAction(MoveBy::create(m_fMoveInternalTime, Vec2(m_fOffsetX, m_fOffsetY)));
        }
        else
        {
            _owner->unscheduleUpdate();
        }
    }
    else
    {
        pNavigationTarget->stopAllActions();
        
        float x = MAX(m_BoundRect.origin.x, pNavigationTarget->getPositionX());
        float y = MAX(m_BoundRect.origin.y, pNavigationTarget->getPositionY());
        x = MIN(x, pTmxHelperCtrl->getMapViewWidth());
        y = MIN(y, pTmxHelperCtrl->getMapViewHeight());
        pNavigationTarget->setPosition(x, y);
        
        _owner->unscheduleUpdate();
    }
}















