//
//  InteractiveController.cpp
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#include "InteractiveController.h"
#include "GlobelDefine.h"
#include "BulletController.h"
USING_NS_CC;

bool InteractiveController::init()
{
    _name = "InteractiveController";
    return true;
}

void InteractiveController::onAdd()
{
    ComController::onAdd();
    
    EventListenerTouchOneByOne* pTouchListener = EventListenerTouchOneByOne::create();
    pTouchListener->onTouchBegan = CC_CALLBACK_2(InteractiveController::touchCallback, this);
    _owner->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchListener, _owner);
}

bool InteractiveController::touchCallback(Touch* pTouch, Event* pEvent)
{
    Vec2 touchPt = _owner->convertToNodeSpace(pTouch->getLocation());
    addBullet(touchPt);
    
    return true;
}

void InteractiveController::addBullet(const cocos2d::Vec2& ptTouch)
{
    Sprite* pBulletSprite = Sprite::create("res/ui/Projectile.png");
    _owner->addChild(pBulletSprite);
    pBulletSprite->setTag(BULLET_TAG);
    
    PhysicsBody* pBulletBody = PhysicsBody::createCircle(pBulletSprite->getContentSize().width*0.5f);
    pBulletBody->setGravityEnable(false);
    pBulletBody->setCategoryBitmask(BULLET_CONTACT_MASK_CATEGREY);
    pBulletBody->setCollisionBitmask(BULLET_CONTACT_MASK_COLLISION);
    pBulletBody->setContactTestBitmask(BULLET_CONTACT_MASK_CONTACTTEST);
    pBulletSprite->addComponent(pBulletBody);
    
    pBulletSprite->addComponent(cocostudio::ComAudio::create());
    pBulletSprite->addComponent(BulletController::createWithTouchPt(ptTouch));
}




























