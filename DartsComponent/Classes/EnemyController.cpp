//
//  EnemyController.cpp
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#include "EnemyController.h"

#include "MacrosAssert.h"
#include "GameEndController.h"

USING_NS_CC;

bool EnemyController::init()
{
    _name = "EnemyController";
    
    return true;
}

void EnemyController::onAdd()
{
    ComController::onAdd();
    
    Size winSize = Director::getInstance()->getWinSize();
    float minY = _owner->getContentSize().height*0.5f;
    float maxY = winSize.height -  _owner->getContentSize().height*0.5f;
    float randomY = RandomHelper::random_real(minY, maxY);

    _owner->setPosition(winSize.width + _owner->getContentSize().width*0.5f,
                        randomY);
    
    int minDuration = 2;
    int maxDuration = 4;
    int randomDuration = RandomHelper::random_int(minDuration, maxDuration);
    
    GameEndController* pGameEndController = static_cast<GameEndController*>(_owner->getParent()->getComponent("GameEndController"));
    CC_RETURN_IF_ASSERT_FAIL(pGameEndController != nullptr);
    
    FiniteTimeAction* actionMove = MoveTo::create(randomDuration,
                                                  Vec2(-_owner->getContentSize().width*0.5f, randomY));
    FiniteTimeAction* actionMoveDone = CallFunc::create(CC_CALLBACK_0(GameEndController::targetMoveFinished, pGameEndController));
    
    _owner->runAction(Sequence::create(actionMove, actionMoveDone, RemoveSelf::create(), nullptr));
}



















