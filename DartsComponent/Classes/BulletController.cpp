//
//  BulletController.cpp
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#include "BulletController.h"
#include "SceneMainGame.h"
USING_NS_CC;
using namespace cocostudio;

BulletController* BulletController::createWithTouchPt(const Vec2& ptTouch)
{
    BulletController *pRet = new(std::nothrow) BulletController();
    if (pRet && pRet->initWithTouchPt(ptTouch))
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

bool BulletController::initWithTouchPt(const cocos2d::Vec2& ptTouch)
{
    _name = "BulletController";
    m_ptTouch = ptTouch;
    
    return true;
}

void BulletController::onAdd()
{
    ComController::onAdd();

    ComAudio* pSceneAudio = static_cast<ComAudio*>(_owner->getComponent("CCComAudio"));
    if (pSceneAudio)
    {
        pSceneAudio->playEffect("res/sound/pew-pew-lei.wav");
    }
    
    LayerMainGame* pMainGameLyr = dynamic_cast<LayerMainGame*>(_owner->getParent());
    if (pMainGameLyr == nullptr)
    {
        return;
    }
    Vec2 playerPosition = pMainGameLyr->getPlayerSprite()->getPosition();
    Size winSize = Director::getInstance()->getWinSize();
    
    Vec2 touchDir = m_ptTouch-playerPosition;
    
    _owner->setPosition(playerPosition);
    float targetDis = fabs(touchDir.length() * winSize.width / (m_ptTouch.x - playerPosition.x));
    touchDir.normalize();
    Vec2 ptTarget = playerPosition + targetDis*touchDir;
    
    float velocity = 480/1; // 480pixels/1sec
    float realMoveDuration = targetDis/velocity;
    ActionInterval* pMoveAction = MoveTo::create(realMoveDuration, ptTarget);
    _owner->runAction(Sequence::create(pMoveAction, RemoveSelf::create(), nullptr));
}


















