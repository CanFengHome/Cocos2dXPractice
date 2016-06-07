//
//  PlayerController.cpp
//  TileMapDemo
//
//  Created by ccf on 16/6/6.
//
//

#include "PlayerController.h"
#include "MacrosAssert.h"
#include "CommonDefine.h"

USING_NS_CC;

bool PlayerController::init()
{
    _name = "PlayerController";
    return true;
}

void PlayerController::onAdd()
{
    CC_RETURN_IF_ASSERT_FAIL(_owner->getParent() != nullptr);
    TMXTiledMap* pTiledMap = _owner->getParent()->getChildByName<TMXTiledMap*>(LAYER_GAME_NAME_NODE_MAP);
    CC_RETURN_IF_ASSERT_FAIL(pTiledMap != nullptr);
    
    TMXObjectGroup* pObjGroup = pTiledMap->getObjectGroup("objects");
    CC_RETURN_IF_ASSERT_FAIL(pObjGroup != nullptr);
    ValueMap initPos = pObjGroup->getObject("PlayerInitPos");
    CC_RETURN_IF_ASSERT_FAIL(!initPos.empty());
    int posX = initPos["x"].asInt();
    int posY = initPos["y"].asInt();
    
    Size tileSize = pTiledMap->getTileSize();
    
    _owner->setPosition(posX + tileSize.width*0.5f, posY + tileSize.height*0.5f);
}






















