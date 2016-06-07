//
//  TmxHelperController.cpp
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#include "TmxHelperController.h"

#include "MacrosAssert.h"
#include "CommonDefine.h"

USING_NS_CC;

bool TmxHelperController::init()
{
    _name = "TmxHelperController";
    return true;
}

void TmxHelperController::onEnter()
{
    ComController::onEnter();
    
    CC_RETURN_IF_ASSERT_FAIL(_owner != nullptr);
    TMXTiledMap* pTiledMap = dynamic_cast<TMXTiledMap*>(_owner);
    CC_RETURN_IF_ASSERT_FAIL(pTiledMap != nullptr);
    
    m_fMapViewWidth = pTiledMap->getTileSize().width * pTiledMap->getMapSize().width;
    m_fMapViewHeight = pTiledMap->getTileSize().height * pTiledMap->getMapSize().height;
    
    m_mapSize = pTiledMap->getMapSize();
    m_tileSize = pTiledMap->getTileSize();
}

Vec2 TmxHelperController::positionToTileCoord(const Vec2& position)
{
    int x = position.x / m_tileSize.width;
    int y = (m_fMapViewHeight - position.y) / m_tileSize.height;
    return Vec2(x, y);
    
//    float x = position.x/pTileMap->getContentSize().width * pTileMap->getMapSize().width;
//    float y = pTileMap->getMapSize().height - position.y/pTileMap->getContentSize().height*pTileMap->getMapSize().height;
//    
//    // 取了当前Tile的最小值(x,y)
//    int iX = floor(x);
//    int iy = floor(y);
//    
//    return Vec2(iX,iy);
}














