//
//  AStarFindPath.cpp
//  AStar
//
//  Created by ccf on 16/6/14.
//  Copyright © 2016年 mfp. All rights reserved.
//

#include "AStarFindPath.h"
#include <cassert>

using namespace std;

namespace AStar
{
    AStarFindPath::AStarFindPath()
    :m_pOpendHeap(nullptr), m_pArrMapData(nullptr), m_iCol(0), m_iRow(0), m_pMapNodes(nullptr), m_iStartX(-1), m_iStartY(-1), m_iEndX(-1), m_iEndY(-1), m_eAstarError(EAStarError::Error_Ok)
    {
        
    }
    
    AStarFindPath::~AStarFindPath()
    {
        if (m_pMapNodes != nullptr)
        {
            delete []m_pMapNodes;
            m_pMapNodes = nullptr;
        }
        
        if (m_pOpendHeap != nullptr)
        {
            delete m_pOpendHeap;
        }
    }
    
    void AStarFindPath::setMapData(unsigned char* pMapData, int col, int row)
    {
        m_pArrMapData = pMapData;
        m_iCol = col;
        m_iRow = row;
        int mapSize = m_iCol * m_iRow;
        m_pOpendHeap = ANodeHeap::createWithMaxSize(mapSize);
        m_arrClosedList.assign(mapSize, nullptr);
        m_pMapNodes = new ANode[mapSize];
        
        reset();
    }
    
    void AStarFindPath::reset()
    {
        ANode* pNodeItem = m_pMapNodes;
        for (int y = 0; y < m_iRow; ++y)
        {
            for (int x = 0; x < m_iCol; ++x)
            {
                pNodeItem->reset();
                pNodeItem->m_iPosX = x;
                pNodeItem->m_iPosY = y;
                ++pNodeItem;
            }
        }
        
        m_iStartX = m_iStartY = -1;
        m_iEndX = m_iEndY = -1;
        m_eAstarError = EAStarError::Error_Ok;
        m_pOpendHeap->reset();
        m_arrClosedList.clear();
    }
    
    vector<PathNode> AStarFindPath::findPath(int startX, int startY, int endX, int endY, int* outNodeNum)
    {
        vector<PathNode> resultPath;
        m_iStartX = startX; m_iStartY = startY;
        m_iEndX = endX; m_iEndY = endY;
        
        if (!canStartFind())
            return resultPath;
        
        ANode* pStartNode = m_pMapNodes + m_iStartY*m_iCol+m_iStartX;
        m_pOpendHeap->push(pStartNode);
        
        bool isFound = false;
        while (!isFound)
        {
            ANode* pCurrNode = m_pOpendHeap->pop();
            if (pCurrNode == nullptr)
                break;
            
            // 1.放入closed
            m_arrClosedList.push_back(pCurrNode);
            pCurrNode->m_iIndex = EAStarIndexType::Index_InClosed;
            
            int expandX = -1;
            int expandY = -1;
            // 2.handler 8方向周边点
            for (int i=0; i<DIR_NUM; ++i)
            {
                expandX = pCurrNode->m_iPosX + ARR_DIR_OFFSET[i][0];
                expandY = pCurrNode->m_iPosY + ARR_DIR_OFFSET[i][1];
                if (!canMove(expandX, expandY))
                    continue;
                
                ANode* pCurExpandNode = m_pMapNodes + expandY*m_iCol + expandX;
                if (pCurExpandNode->m_iIndex == EAStarIndexType::Index_InClosed)
                {
                    continue;
                }
                else
                {
                    int expandNodeG = pCurrNode->m_iG + calBaseCost(ARR_DIR_OFFSET[i][0], ARR_DIR_OFFSET[i][1]) + calAdditionalCost(expandX, expandY);
                    if (pCurExpandNode->m_iIndex == EAStarIndexType::Index_NotUse)
                    {
                        int h = (FAST_ABS(expandX-m_iEndX)+FAST_ABS(expandY-m_iEndY))*AStarCostRightAngle;
                        pCurExpandNode->m_iG = expandNodeG;
                        pCurExpandNode->m_iH = h;
                        pCurExpandNode->m_iF = expandNodeG+h;
                        pCurExpandNode->m_pParent = pCurrNode;
                        m_pOpendHeap->push(pCurExpandNode);
                        if (h == 0)
                        {
                            isFound = true;
                            break;
                        }
                    }
                    else
                    {
                        // 邻居节点在open list中
                        assert(pCurExpandNode->m_iIndex >= 0);
                        // 邻居在open中，则需要看邻居点的G与当前点的G+当前点到邻居点的距离（10、14）的大小
                        // 如果从此点走更近（即G更小），则将此点的父节点换成当前点
                        // 注意：对于同一个点，G小，则F必须小，因为H是相同的
                        // 当父节点改变后，open表中的最小点可能发生变化，需要再次排序得到最小点
                        if (pCurExpandNode->m_iG >= expandNodeG)
                        {
                            pCurExpandNode->m_iG = expandNodeG;
                            pCurExpandNode->m_iF = pCurExpandNode->m_iG + pCurExpandNode->m_iH;
                            pCurExpandNode->m_pParent = pCurrNode;
                            
                            m_pOpendHeap->sortUp(pCurExpandNode->m_iIndex);
                        }
                    }
                }
            }
        }
        
        ANode* pResult = nullptr;
        // isFound
        if (!isFound)
        {
            m_eAstarError = EAStarError::Error_NotFound;
        }
        else
        {
            int num = 0;
            // 首先定位到终点
            pResult = m_pMapNodes + m_iEndY*m_iCol + m_iEndX;
            assert(pResult != nullptr && pResult->m_pParent != nullptr);
            do
            {
                resultPath.push_back({pResult->m_iPosX, pResult->m_iPosY});
                pResult = pResult->m_pParent;
                ++num;
            }while (pResult != nullptr);
            assert(num >= 2);
            *outNodeNum = num;
        }
        
        return resultPath;
    }
    
    int AStarFindPath::calAdditionalCost(int x, int y)
    {
        int addtionalCost = 0;
        if (m_pArrMapData[y*m_iCol + x] == EAStarNodeType::NodeType_Wall)
        {
            addtionalCost += AStarCostWall;
        }
        
        return addtionalCost;
    }
    
    int AStarFindPath::calBaseCost(int xOffset, int yOffset)
    {
        return ((xOffset) == 0 || (yOffset) == 0) ? AStarCostRightAngle : AStarCostDiagonal;
    }
    
    bool AStarFindPath::canMove(int x, int y)
    {
        return (x >= 0 && x < m_iCol && y >= 0 && y < m_iRow) &&
                m_pArrMapData[y*m_iCol+x] != EAStarNodeType::NodeType_Block;
    }
    
    bool AStarFindPath::canStartFind()
    {
        if (!m_pArrMapData || m_iCol > MAP_MAX_COL || m_iRow > MAP_MAX_ROW)
        {
            m_eAstarError = EAStarError::Error_Map;
            return false;
        }
        
        if (!canMove(m_iStartX, m_iStartY))
        {
            m_eAstarError = EAStarError::Error_StartNotValid;
            return false;
        }
        
        if (!canMove(m_iEndX, m_iEndY))
        {
            m_eAstarError = EAStarError::Error_DestNotValid;
            return false;
        }
        
        if (m_iStartX == m_iEndX && m_iStartY == m_iEndY)
        {
            m_eAstarError = EAStarError::Error_ErrorSamePoint;
            return false;
        }
        
        return true;
    }
    
    string AStarFindPath::getError() const
    {
        switch (m_eAstarError)
        {
            case EAStarError::Error_Ok:
                return "";
            case EAStarError::Error_Map:
                return "map error";
            case EAStarError::Error_DestNotValid:
                return "set dest position error";
            case EAStarError::Error_ErrorSamePoint:
                return "start position == end position";
            case EAStarError::Error_NotFound:
                return "not find path";
            case EAStarError::Error_StartNotValid:
                return "set start position error";
        }
    }
}





















