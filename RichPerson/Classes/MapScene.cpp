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
#include "GameController.h"

#include "GameConvertTool.h"

using namespace std;
USING_NS_CC;
using namespace cocos2d::ui;

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

MapLayer::~MapLayer()
{
    CC_SAFE_RELEASE_NULL(m_pMapWayData);
    CC_SAFE_RELEASE_NULL(m_pGameCtrl);
    _eventDispatcher->removeAllEventListeners();
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
    
    m_pGameCtrl = GameController::createWithMapLayer(this);
    assert(m_pGameCtrl != nullptr);
    m_pGameCtrl->retain();
    
    Size mapSize = m_pTiledMap->getMapSize();
    m_pMapWayData = MapWayData::createWithRowColCount(mapSize.height, mapSize.width);
    assert(m_pMapWayData != nullptr);
    m_pMapWayData->retain();

    addRightBanner();
    drawTable(2);
    
    setWayPassToGrid();
    addPlayer();
    addGoButton();
    refreshRoundDisplay();
    
    EventListenerCustom* pEventHeroAdd = EventListenerCustom::create(EVENT_CUSTOM_RICHER_MSG, CC_CALLBACK_1(MapLayer::handlerEventRicherMsg, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pEventHeroAdd, this);
    
    return true;
}

bool MapLayer::addTiledMap()
{
    string strMapTmxFile = __String::createWithFormat("res/map/map_%d.tmx", m_iMapIndex+1)->getCString();
    if (!FileUtils::getInstance()->isFileExist(strMapTmxFile))
    {
        return false;
    }
    m_pTiledMap = TMXTiledMap::create(strMapTmxFile);
    addChild(m_pTiledMap);
    
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
    
    m_pPlayer1 = RicherPlayer::createWithPlayerType(EPlayerType::Player1);
    int randIndex1 = RandomHelper::random_int(0, (int)(m_arrWayLayerPassPosition.size()-1));
    Vec2 vec2ForPlayer1 = m_arrWayLayerPassPosition.at(randIndex1) + Vec2(PlayerSizeWidth*0.5f, PlayerSizeHeight*0.5f);
    m_pPlayer1->setPosition(vec2ForPlayer1);
    addChild(m_pPlayer1);
 
    m_pPlayer2 = RicherPlayer::createWithPlayerType(EPlayerType::Player2);
    int randIndex2 = RandomHelper::random_int(0, (int)(m_arrWayLayerPassPosition.size()-1));
    Vec2 vec2ForPlayer2 = m_arrWayLayerPassPosition.at(randIndex2) + Vec2(PlayerSizeWidth*0.5f, PlayerSizeHeight*0.5f);
    m_pPlayer2->setPosition(vec2ForPlayer2);
    addChild(m_pPlayer2);
}

void MapLayer::setWayPassToGrid()
{
    assert(m_pMapWayData != nullptr);
    m_pWayLayer = m_pTiledMap->getLayer("way");
    
    Size mapSize = m_pWayLayer->getLayerSize();
    
    for (int row = 0; row < mapSize.height; ++row)
    {
        for (int col = 0; col < mapSize.width; ++col)
        {
            Sprite* pWaySprite = m_pWayLayer->getTileAt(Vec2(col, row));
            if (pWaySprite != nullptr)
            {
                float x = pWaySprite->getPositionX();
                float y = pWaySprite->getPositionY();
                int gridColIndex = x / tiledWidth;
                int gridRowIndex = y / tiledHeight;
                m_pMapWayData->setGridCanPass(true, GridIndex(gridRowIndex, gridColIndex));
                
                // 记录道路层中道路的场景坐标
                m_arrWayLayerPassPosition.push_back(pWaySprite->getPosition());
            }
        }
    }
}

void MapLayer::addGoButton()
{
    m_pBtnGo = Button::create("res/button/go_normal.png","res/button/go_press.png");
    m_pBtnGo->setPressedActionEnabled(true);
    m_pBtnGo->setTitleFontSize(25);
    addChild(m_pBtnGo);
    
    m_pBtnGo->addTouchEventListener(CC_CALLBACK_2(MapLayer::btnGoCallback, this));
    m_pBtnGo->setPosition(Vec2(tableStartPosition_x + 2 * tableWidth, tableStartPosition_y - tableHeight * 6));
}

void MapLayer::btnGoCallback(Ref *pSender, Widget::TouchEventType pTouchEventType)
{
    if (pTouchEventType == Widget::TouchEventType::ENDED && m_pGameCtrl != nullptr)
    {
        m_pGameCtrl->startRolesWalking();
    }
}

void MapLayer::refreshRoundDisplay()
{
    if (m_pLblGameRound == nullptr)
    {
        m_pLblGameRound = Label::create();
        m_pLblGameRound->setSystemFontSize(24.0f);
        m_pLblGameRound->setTextColor(Color4B::WHITE);
        addChild(m_pLblGameRound);
        m_pLblGameRound->setAnchorPoint(Vec2(0.0f,0.5f));
        m_pLblGameRound->setPosition(tableStartPosition_x + 50.0f, 50.0f);
    }
    
    if (m_pGameCtrl != nullptr)
    {
        m_pLblGameRound->setString(Value(m_pGameCtrl->getGameRoundCount()).asString());
    }
}

void MapLayer::handlerEventRicherMsg(EventCustom* event)
{
    assert(event != nullptr);
    __Integer* pEventGoStatus = static_cast<__Integer*>(event->getUserData());
    assert(pEventGoStatus != nullptr);
    
    switch (pEventGoStatus->getValue())
    {
        case MSG_GO_SHOW_TAG:
        {
            m_pBtnGo->runAction(MoveBy::create(0.3f, Vec2(-m_pBtnGo->getContentSize().width * 2.0f, 0.0f)));
            refreshRoundDisplay();
            break;
        }
        case  MSG_GO_HIDE_TAG:
        {
            m_pBtnGo->runAction(MoveBy::create(0.3f, Vec2(m_pBtnGo->getContentSize().width * 2.0f, 0.0f)));
            break;
        }
    }
}















