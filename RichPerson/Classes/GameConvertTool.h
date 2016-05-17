//
//  GameConvertTool.h
//  RichPerson
//
//  Created by mfp on 16/5/17.
//
//

#ifndef GameConvertTool_h
#define GameConvertTool_h

#include "RicherPlayer.h"
#include "MapWayData.h"
#include "RouteNavigation.h"

class GameConvertTool
{
public:
    static GridIndex convertPlayerToGridIndex(RicherPlayer* pPlayer);
    static cocos2d::Vec2 convertGridIndexToPlayerPosition(const GridIndex& gridIndex);
    static ENavigationDirection calculateNavigationDir(const NavigationUnit& navigationData);
    static void printRouteInfo(const std::string& strPlayerName, const vector<NavigationUnit>& arrMovePath);
};

#endif /* GameConvertTool_h */
