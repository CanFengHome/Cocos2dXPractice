//
//  SceneGame.cpp
//  TileMapDemo
//
//  Created by ccf on 16/6/6.
//
//

#include "SceneGame.h"

#include "MacrosAssert.h"
#include "CommonDefine.h"
#include "PlayerController.h"
#include "NavigateController.h"
#include "UpdateViewController.h"
#include "TmxHelperController.h"
#include "TmxCollisionController.h"

USING_NS_CC;

bool SceneGame::init()
{
    LayerGame* pLyr = LayerGame::create();
    pLyr->setName(LAYER_GAME_NAME);
    addChild(pLyr);
    
    Node* pNavigationNode = Node::create();
    addChild(pNavigationNode);
    pNavigationNode->addComponent(NavigateController::create());
    
    return true;
}


bool LayerGame::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    m_pTiledMap = TMXTiledMap::create("res/map/map.tmx");
    CC_RETURN_VALUE_IF_ASSERT_FAIL(m_pTiledMap != nullptr, false);
    addChild(m_pTiledMap);
    m_pTiledMap->setName(LAYER_GAME_NAME_NODE_MAP);
    m_pTiledMap->addComponent(TmxHelperController::create());
    m_pTiledMap->addComponent(TmxCollisionController::create());
    
    m_pPlayer = Sprite::create("res/player/Player.png");
    CC_RETURN_VALUE_IF_ASSERT_FAIL(m_pPlayer != nullptr, false);
    addChild(m_pPlayer);
    m_pPlayer->setName(LAYER_GAME_NAME_NODE_PLAYER);
    m_pPlayer->addComponent(PlayerController::create());
    
    addComponent(UpdateViewController::create());
    
    return true;
}

























