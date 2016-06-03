//
//  GameEndController.cpp
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#include "GameEndController.h"

#include "MacrosAssert.h"
#include "LayerGameOver.h"
#include "GlobelDefine.h"

using namespace cocostudio;
USING_NS_CC;

bool GameEndController::init()
{
    _name = "GameEndController";
    m_iKillCount = 0;
    
    return true;
}

void GameEndController::targetMoveFinished()
{
    SceneGameOver* pGameOverScene = SceneGameOver::createWithScore(false, m_iKillCount);
    Director::getInstance()->replaceScene(pGameOverScene);
}

void GameEndController::onAdd()
{
    ComController::onAdd();
    ComAudio* pSceneAudio = static_cast<ComAudio*>(_owner->getComponent("CCComAudio"));
    if (pSceneAudio)
    {
        pSceneAudio->playBackgroundMusic("res/sound/background.wav", true);
    }
    
    EventListenerPhysicsContact* pContactListener = EventListenerPhysicsContact::create();
    pContactListener->onContactBegin = CC_CALLBACK_1(GameEndController::contactCallback, this);
    _owner->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pContactListener, _owner);
}

bool GameEndController::contactCallback(PhysicsContact& contact)
{
    Node* pA = contact.getShapeA()->getBody()->getNode();
    Node* pB = contact.getShapeB()->getBody()->getNode();
    
    CC_RETURN_VALUE_IF_ASSERT_FAIL(pA != nullptr && pB != nullptr, true);
    if ((pA->getTag() == BULLET_TAG && pB->getTag() == ENEMY_TAG) ||
        (pB->getTag() == BULLET_TAG && pA->getTag() == ENEMY_TAG))
    {
        pA->removeFromParent();
        pB->removeFromParent();
        ++m_iKillCount;
    }
    
    return true;
}






















