//
//  MapWayData.cpp
//  RichPerson
//
//  Created by mfp on 16/5/16.
//
//

#include "MapWayData.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

MapWayData* MapWayData::createWithRowColCount(int gridRowCount, int gridColCount)
{
    MapWayData *pRet = new(std::nothrow) MapWayData();
    if (pRet && pRet->initWithRowColCount(gridRowCount, gridColCount))
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

MapWayData::~MapWayData()
{
    m_arrCanPassGrid.clear();
}

bool MapWayData::initWithRowColCount(int gridRowCount, int gridColCount)
{
    m_iColCount = gridColCount;
    m_iRowCount = gridRowCount;
    
    m_arrCanPassGrid.assign(m_iRowCount*m_iColCount, false);
    
    return true;
}

void MapWayData::setGridCanPass(bool bCanPass, const GridIndex& gridIndex)
{
#if _DEBUG
    assert(checkGridIndex(gridIndex));
#endif
    int vectorIndex = convertGridIndexToVecotrIndex(gridIndex);
    m_arrCanPassGrid[vectorIndex] = bCanPass;
}

bool MapWayData::getGridCanPass(const GridIndex& gridIndex) const
{
#if _DEBUG
    assert(checkGridIndex(gridIndex));
#endif
    int vectorIndex = convertGridIndexToVecotrIndex(gridIndex);
    return m_arrCanPassGrid[vectorIndex];
}

int MapWayData::convertGridIndexToVecotrIndex(const GridIndex& gridIndex) const
{
    return gridIndex.RowIndex * m_iColCount + gridIndex.ColIndex;
}

GridIndex MapWayData::convertVectorIndexToGridIndex(int vectorIndex) const
{
    return GridIndex(vectorIndex / m_iColCount, vectorIndex % m_iColCount);
}

MapWayData MapWayData::getDataClone() const
{
    MapWayData data;
    data.m_iColCount = this->m_iColCount;
    data.m_iRowCount = this->m_iRowCount;
    data.m_arrCanPassGrid = this->m_arrCanPassGrid;
    return data;
}

void MapWayData::printWayData() const
{
    if (m_arrCanPassGrid.empty())
    {
        return;
    }
    
    CCLOG("-------------way--------");
    for (int row = 0; row < m_iRowCount; ++row)
    {
        __String* pWayRowInfo = __String::create("");
        pWayRowInfo->appendWithFormat("row%d:", row);
        for (int col = 0; col < m_iColCount; ++col)
        {
            if (getGridCanPass(GridIndex(row, col)))
            {
                pWayRowInfo->appendWithFormat(" (%d, %d)", row, col);
            }
        }
        
        if (pWayRowInfo->length() > 6)
        {
            CCLOG("%s", pWayRowInfo->getCString());
        }
    }
    CCLOG("-------------way--------");
}

#if _DEBUG
bool MapWayData::checkGridIndex(const GridIndex& gridIndex)
{
    if (gridIndex.RowIndex >= 0 && gridIndex.RowIndex < m_iRowCount &&
        gridIndex.ColIndex >= 0 && gridIndex.ColIndex < m_iColCount)
    {
        return true;
    }
    
    return false;
}
#endif

























