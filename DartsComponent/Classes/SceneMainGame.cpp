//
//  SceneMainGame.cpp
//  DartsComponent
//
//  Created by ccf on 16/6/2.
//
//

#include "SceneMainGame.h"

#include "2d/CCComponent.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

#include "AddTargetController.h"
#include "GameEndController.h"
#include "InteractiveController.h"

bool SceneMainGame::init()
{
    if (!initWithPhysics())
    {
        return false;
    }
    
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    LayerMainGame* pLyrMain = LayerMainGame::create();
    addChild(pLyrMain);
    
    return true;
}

bool LayerMainGame::init()
{
    if (!LayerColor::initWithColor(Color4B::GRAY))
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    m_pPlayerSprite = Sprite::create("res/ui/Player.png");
    addChild(m_pPlayerSprite);
    m_pPlayerSprite->addComponent(ComAudio::create());
    m_pPlayerSprite->setPosition(m_pPlayerSprite->getContentSize().width*0.5f,
                                 winSize.height*0.5f);
    
    addComponent(ComAudio::create());
    addComponent(GameEndController::create());
    addComponent(AddTargetController::create());
    addComponent(InteractiveController::create());
    
    return true;
}






























