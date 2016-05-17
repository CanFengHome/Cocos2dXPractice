//
//  GameConvertTool.cpp
//  RichPerson
//
//  Created by mfp on 16/5/17.
//
//

#include "GameConvertTool.h"
#include "MapSceneDefine.h"

USING_NS_CC;

GridIndex GameConvertTool::convertPlayerToGridIndex(RicherPlayer* pPlayer)
{
    assert(pPlayer != nullptr);
    Vec2 playerPosition = pPlayer->getPosition();
    
    return GridIndex((int)((playerPosition.y - PlayerSizeHeight*0.5f)/tiledHeight),
                     (int)((playerPosition.x - PlayerSizeWidth*0.5f)/tiledWidth));
}

Vec2 GameConvertTool::convertGridIndexToPlayerPosition(const GridIndex& gridIndex)
{
    return Vec2(gridIndex.ColIndex*tiledWidth + PlayerSizeWidth*0.5f,
                gridIndex.RowIndex*tiledHeight + PlayerSizeHeight*0.5f);
}

ENavigationDirection GameConvertTool::calculateNavigationDir(const NavigationUnit& navigationData)
{
    const GridIndex& currGridIndex = navigationData.CurrGridIndex;
    const GridIndex& nextGridIndex = navigationData.NextGridIndex;
 
    assert(currGridIndex.RowIndex != nextGridIndex.RowIndex ||
           currGridIndex.ColIndex != nextGridIndex.ColIndex);
    
    if (currGridIndex.ColIndex == nextGridIndex.ColIndex)
    {
        return currGridIndex.RowIndex < nextGridIndex.RowIndex?(ENavigationDirection::Up):(ENavigationDirection::Down);
    }
    else// if (currGridIndex.RowIndex == nextGridIndex.RowIndex)
    {
        return currGridIndex.ColIndex < nextGridIndex.ColIndex?(ENavigationDirection::Right):(ENavigationDirection::Left);
    }
}

void GameConvertTool::printRouteInfo(const std::string& strPlayerName, const vector<NavigationUnit>& arrMovePath)
{
    __String* pInfo = __String::create(strPlayerName);
    pInfo->append(":");
    
    for (const NavigationUnit& pItem: arrMovePath)
    {
        pInfo->appendWithFormat(" (%d,%d)", pItem.CurrGridIndex.RowIndex, pItem.CurrGridIndex.ColIndex);
    }
    
    CCLOG("%s", pInfo->getCString());
}


























