//
//  AddTargetController.cpp
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#include "AddTargetController.h"
#include "EnemyController.h"
#include "GlobelDefine.h"

using namespace cocostudio;
USING_NS_CC;


bool AddTargetController::init()
{
    _name = "AddTargetController";
    
    m_fElapsedTime = 0.0f;
    m_fAddTargetTime = 1.0f;
    
    return true;
}

void AddTargetController::update(float delta)
{
    m_fElapsedTime += delta;
    if (m_fElapsedTime >= m_fAddTargetTime)
    {
        addTarget();
        m_fElapsedTime = 0;
    }
}

void AddTargetController::addTarget()
{
    Sprite *pTargetSprite = Sprite::create("res/ui/Target.png", Rect(0,0,27,40));
    _owner->addChild(pTargetSprite);
    pTargetSprite->setTag(ENEMY_TAG);
    pTargetSprite->addComponent(EnemyController::create());
    
    PhysicsBody* pEnemyBody = PhysicsBody::createBox(pTargetSprite->getContentSize());
    pEnemyBody->setGravityEnable(false);
    pEnemyBody->setCategoryBitmask(ENEMY_CONTACT_MASK_CATEGREY);
    pEnemyBody->setCollisionBitmask(ENEMY_CONTACT_MASK_COLLISION);
    pEnemyBody->setContactTestBitmask(ENEMY_CONTACT_MASK_CONTACTTEST);
    pTargetSprite->addComponent(pEnemyBody);
}


















