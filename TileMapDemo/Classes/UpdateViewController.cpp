//
//  UpdateViewController.cpp
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#include "UpdateViewController.h"

#include "MacrosAssert.h"
#include "CommonDefine.h"
#include "TmxHelperController.h"

USING_NS_CC;

bool UpdateViewController::init()
{
    _name = "UpdateViewController";
    return true;
}

void UpdateViewController::onEnter()
{
    ComController::onEnter();
    
    updateView();
}

void UpdateViewController::updateView() const
{
    CC_RETURN_IF_ASSERT_FAIL(_owner != nullptr);
    
    Node* pReferenceObj = _owner->getChildByName(LAYER_GAME_NAME_NODE_PLAYER);
    CC_RETURN_IF_ASSERT_FAIL(pReferenceObj);
    
    Node* pTmxLayer = _owner->getChildByName(LAYER_GAME_NAME_NODE_MAP);
    CC_RETURN_IF_ASSERT_FAIL(pTmxLayer != nullptr);
    
    TmxHelperController* pTmxHelperCtrl = dynamic_cast<TmxHelperController*>(pTmxLayer->getComponent("TmxHelperController"));
    CC_RETURN_IF_ASSERT_FAIL(pTmxHelperCtrl != nullptr);
    
    Size winSize = Director::getInstance()->getWinSize();
    float x = MAX(pReferenceObj->getPositionX(), winSize.width*0.5f);
    float y = MAX(pReferenceObj->getPositionY(), winSize.height*0.5f);
    x = MIN(x, pTmxHelperCtrl->getMapViewWidth() - winSize.width*0.5f);
    y = MIN(y, pTmxHelperCtrl->getMapViewHeight() - winSize.height*0.5f);
    
    Vec2 offset = Vec2(winSize*0.5f) - Vec2(x, y);
    _owner->setPosition(offset);
}























