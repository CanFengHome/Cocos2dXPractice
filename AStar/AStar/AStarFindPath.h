//
//  AStarFindPath.h
//  AStar
//
//  Created by ccf on 16/6/14.
//  Copyright © 2016年 mfp. All rights reserved.
//

#ifndef AStarFindPath_h
#define AStarFindPath_h

#include <vector>
#include <string>

#include "AStarDefine.h"
#include "ANodeHeap.h"

namespace AStar
{
    class AStarFindPath
    {
    public:
        AStarFindPath();
        ~AStarFindPath();
        void setMapData(unsigned char* pMapData, int col, int row);
        std::vector<PathNode> findPath(int startX, int startY, int endX, int endY, int* outNodeNum);
        // 第二次调用findPath前外部必须调用清空原数据状态
        void reset();
        std::string getError() const;
    private:
        inline bool canMove(int x, int y);
        bool canStartFind();
        
        inline int calBaseCost(int xOffset, int yOffset);
        inline int calAdditionalCost(int x, int y);
    private:
        std::vector<ANode*> m_arrClosedList;
        ANodeHeap* m_pOpendHeap;
        unsigned char* m_pArrMapData;
        int m_iCol;
        int m_iRow;

        ANode* m_pMapNodes;
        
        int m_iStartX;
        int m_iStartY;
        int m_iEndX;
        int m_iEndY;
        EAStarError m_eAstarError;
    };
}

#endif /* AStarFindPath_h */
