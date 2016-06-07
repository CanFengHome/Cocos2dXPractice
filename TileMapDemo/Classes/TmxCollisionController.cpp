//
//  TmxCollisionController.cpp
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#include "TmxCollisionController.h"

#include "MacrosAssert.h"
#include "CommonDefine.h"
#include "TmxHelperController.h"

USING_NS_CC;

bool TmxCollisionController::init()
{
    _name = "TmxCollisionController";
    return true;
}

void TmxCollisionController::onEnter()
{
    ComController::onEnter();
}

bool TmxCollisionController::isCollision(const Vec2& position)
{
    CC_RETURN_VALUE_IF_ASSERT_FAIL(_owner != nullptr, false);
    
    TMXTiledMap* pTiledMap = dynamic_cast<TMXTiledMap*>(_owner);
    CC_RETURN_VALUE_IF_ASSERT_FAIL(pTiledMap != nullptr, false);
    TMXLayer* pMetaLayer = pTiledMap->getLayer("meta");
    CC_RETURN_VALUE_IF_ASSERT_FAIL(pMetaLayer != nullptr, false);
    
    TmxHelperController* pTmxHelperCtrl = dynamic_cast<TmxHelperController*>(_owner->getComponent("TmxHelperController"));
    CC_RETURN_VALUE_IF_ASSERT_FAIL(pTmxHelperCtrl != nullptr, false);
    
    Vec2 tiledCoord = pTmxHelperCtrl->positionToTileCoord(position);
    int tileGid = pMetaLayer->getTileGIDAt(tiledCoord);
    if (tileGid)
    {
        ValueMap tileProperty = pTiledMap->getPropertiesForGID(tileGid).asValueMap();
        if (tileProperty.empty())
        {
            return false;
        }
        return tileProperty["collidable"].asBool();
    }
    
    return false;
}














