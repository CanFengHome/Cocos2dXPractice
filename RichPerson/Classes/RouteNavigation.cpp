//
//  RouteNavigation.cpp
//  RichPerson
//
//  Created by mfp on 16/5/17.
//
//

#include "RouteNavigation.h"
#include "GameConvertTool.h"
#include "RicherPlayer.h"

USING_NS_CC;

vector<NavigationUnit> RouteNavigation::getMovePath(RicherPlayer* pPlayer, MapWayData* pMapWayData, int moveStep)
{
    assert(pPlayer != nullptr && pMapWayData != nullptr);
    assert(moveStep >= 1 && moveStep <= 6);
    
    vector<NavigationUnit> resultPath;
    MapWayData currMapWayData = pMapWayData->getDataClone();
    GridIndex currGridIndex = GameConvertTool::convertPlayerToGridIndex(pPlayer);
    ENavigationDirection currDir = pPlayer->getCurrDir();
    
    int currStep = 0;
    // up right down left
    GridIndex arrCurrGridRound[4] = {GridIndex(0,1), GridIndex(1,0), GridIndex(0,-1), GridIndex(-1,0)};
    currMapWayData.setGridCanPass(false, currGridIndex);
    while (currStep < moveStep)
    {
        vector<GridIndex> arrNextGridIndexs;
        for (int i=0; i<4; ++i)
        {
            const GridIndex& nextGridIndex = currGridIndex.add(arrCurrGridRound[i]);
            if (currMapWayData.getGridCanPass(nextGridIndex))
            {
                arrNextGridIndexs.push_back(nextGridIndex);
            }
        }
        
        // 地图要求路径没有断路的情况
        assert(!arrNextGridIndexs.empty());
        
        // 保证尽可能的沿着原先的方向行走，在十字路口或者T行路口，方向随机
        int findNextIndex = -1;
        if (arrNextGridIndexs.size() == 2 &&
            (arrNextGridIndexs[0].RowIndex == arrNextGridIndexs[1].RowIndex || arrNextGridIndexs[0].ColIndex == arrNextGridIndexs[1].ColIndex))
        {
            if (GameConvertTool::calculateNavigationDir(NavigationUnit(currGridIndex, arrNextGridIndexs[0])) == currDir)
            {
                findNextIndex = 0;
            }
            else
            {
                findNextIndex = 1;
            }
        }
        else
        {
            findNextIndex = RandomHelper::random_int(0, (int)arrNextGridIndexs.size()-1);
        }
        assert(findNextIndex >= 0 && findNextIndex < arrNextGridIndexs.size());
        const GridIndex& nextGridIndex = arrNextGridIndexs[findNextIndex];
        
        NavigationUnit stepUnit = NavigationUnit(currGridIndex, nextGridIndex);
        resultPath.push_back(stepUnit);
        currGridIndex = nextGridIndex;
        currMapWayData.setGridCanPass(false, nextGridIndex);
        ++currStep;
        currDir = GameConvertTool::calculateNavigationDir(stepUnit);
    }
    
    return resultPath;
}


























