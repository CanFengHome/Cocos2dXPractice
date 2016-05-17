//
//  GameController.cpp
//  RichPerson
//
//  Created by mfp on 16/5/17.
//
//

#include <vector>
#include "GameController.h"
#include "RouteNavigation.h"
#include "MapSceneDefine.h"
#include "GameConvertTool.h"

using namespace std;
USING_NS_CC;

GameController* GameController::createWithMapLayer(MapLayer* pMapLyr)
{
    GameController *pRet = new(std::nothrow) GameController();
    if (pRet && pRet->initWithMapLayer(pMapLyr))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool GameController::initWithMapLayer(MapLayer *pMapLyr)
{
    m_pMapLyr = pMapLyr;
    m_iGameRoundCount = 0;
    
    return true;
}

void GameController::startRolesWalking()
{
    assert(m_pMapLyr != nullptr);
    ++m_iGameRoundCount;
    
    EventCustom eventRicherMsg(EVENT_CUSTOM_RICHER_MSG);
    eventRicherMsg.setUserData(__Integer::create(MSG_GO_HIDE_TAG));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventRicherMsg);
    
    RicherPlayer* pPlayer1 = m_pMapLyr->getPlayer1();
    int randomMoveStep = RandomHelper::random_int(1, 6);
    const vector<NavigationUnit>& arrMovePath = RouteNavigation::getMovePath(pPlayer1, m_pMapLyr->getMapWayData(), randomMoveStep);
//    // print move path
//    GameConvertTool::printRouteInfo("Player1", arrMovePath);
    pPlayer1->moveByRoute(arrMovePath, CC_CALLBACK_0(GameController::player1WalkingFinish, this));
}

void GameController::player1WalkingFinish()
{
    RicherPlayer* pPlayer2 = m_pMapLyr->getPlayer2();
    int randomMoveStep = RandomHelper::random_int(1, 6);
    const vector<NavigationUnit>& arrMovePath = RouteNavigation::getMovePath(pPlayer2, m_pMapLyr->getMapWayData(), randomMoveStep);
    //    // print move path
    //    GameConvertTool::printRouteInfo("Player2", arrMovePath);
    pPlayer2->moveByRoute(arrMovePath, CC_CALLBACK_0(GameController::player2WalkingFinish, this));
}

void GameController::player2WalkingFinish()
{
    EventCustom eventRicherMsg(EVENT_CUSTOM_RICHER_MSG);
    eventRicherMsg.setUserData(__Integer::create(MSG_GO_SHOW_TAG));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventRicherMsg);
}















