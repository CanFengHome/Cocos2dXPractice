//
//  MapScene.cpp
//  RichPerson
//
//  Created by mfp on 16/5/12.
//
//

#include <string>
#include "MapScene.h"
#include "MapSceneDefine.h"

using namespace std;
USING_NS_CC;


#pragma mark MapLayer

Scene* MapLayer::createWithMapIndex(int mapIndex)
{
    MapLayer *pRet = new(std::nothrow) MapLayer();
    if (pRet && pRet->initWithMapIndex(mapIndex))
    {
        pRet->autorelease();
        
        Scene* pMapScene = Scene::create();
        pMapScene->addChild(pRet);
        
        return pMapScene;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MapLayer::initWithMapIndex(int mapIndex)
{
    if (!Layer::init())
    {
        return false;
    }
    m_iMapIndex = mapIndex;

    if (!addTiledMap())
    {
        return false;
    }
    addRightBanner();
    drawTable(2);
    addPlayer();
    
    return true;
}

bool MapLayer::addTiledMap()
{
    string strMapTmxFile = __String::createWithFormat("res/map/map_%d.tmx", m_iMapIndex+1)->getCString();
    if (!FileUtils::getInstance()->isFileExist(strMapTmxFile))
    {
        return false;
    }
    m_tiledMap = TMXTiledMap::create(strMapTmxFile);
    addChild(m_tiledMap);
    
    return true;
}

void MapLayer::addRightBanner()
{
    Sprite* rightBanner = Sprite::create("res/map/right_banner.png");
    rightBanner->setAnchorPoint(Vec2::ZERO);
    rightBanner->setPosition(tableStartPosition_x, 0.0f);
    addChild(rightBanner);
}

void MapLayer::drawTable(int playerNumber)
{
    DrawNode* pDrawNode = DrawNode::create();
    this->addChild(pDrawNode);
    
    for(int i=0;i<playerNumber;i++)
    {
        pDrawNode->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y-2*i*tableHeight),
                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y-2*i*tableHeight), 1,
                          Color4F(0, 1, 0, 1));
        
        pDrawNode->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y - 2*(i+1)*tableHeight),
                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - 2*(i+1)*tableHeight), 1,
                          Color4F(0, 1, 0, 1));
        
        pDrawNode->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight),
                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 1,
                          Color4F(0, 1, 0, 1));
        
        pDrawNode->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2*i*tableHeight),
                          Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2* tableHeight-2*i*tableHeight), 1, 
                          Color4F(0, 1, 0, 1));
    }
}

void MapLayer::addPlayer()
{
    Sprite* pPlayer1 = Sprite::create(PLAYER_1);
    pPlayer1->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - tableHeight);
    addChild(pPlayer1);
    
    Label* pLblPlayer1Money = Label::create();
    pLblPlayer1Money->setString("$");
    pLblPlayer1Money->setAnchorPoint(Vec2(0, 0.5));
    pLblPlayer1Money->setSystemFontSize(25.0f);
    pLblPlayer1Money->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2);
    addChild(pLblPlayer1Money);
    
    Label *pLblPlayer1Strength = Label::create();
    pLblPlayer1Strength->setString("+");
    pLblPlayer1Strength->setAnchorPoint(Vec2(0, 0.5));
    pLblPlayer1Strength->setSystemFontSize(28);
    pLblPlayer1Strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3);
    addChild(pLblPlayer1Strength);
    
    Sprite* pPlayer2 = Sprite::create(PLAYER_2);
    pPlayer2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
    addChild(pPlayer2);
    
    Label* pLblPlayer2Money = Label::create();
    pLblPlayer2Money->setString("$");
    pLblPlayer2Money->setAnchorPoint(Vec2(0, 0.5));
    pLblPlayer2Money->setSystemFontSize(25);
    pLblPlayer2Money->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5);
    addChild(pLblPlayer2Money);
    
    Label* pLblPlayer2Strength = Label::create();
    pLblPlayer2Strength->setString("+");
    pLblPlayer2Strength->setAnchorPoint(Vec2(0, 0.5));
    pLblPlayer2Strength->setSystemFontSize(28);
    pLblPlayer2Strength->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7);
    addChild(pLblPlayer2Strength);
}


























