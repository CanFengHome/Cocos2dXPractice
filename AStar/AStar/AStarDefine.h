//
//  AStarDefine.h
//  AStar
//
//  Created by ccf on 16/6/12.
//  Copyright © 2016年 mfp. All rights reserved.
//

#ifndef AStarDefine_h
#define AStarDefine_h

// 参考资料来源  http://blog.csdn.net/shanshanpt/article/details/8977512

namespace AStar
{
    #define FAST_ABS(d) ((d) < 0 ? -(d) : (d))
    
    // 方向定义
    const int DIR_NUM = 8;
    // 方向偏移
    const int ARR_DIR_OFFSET[DIR_NUM][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // 右左下上
        {1, 1}, {1, -1}, {-1, 1}, {-1 -1} // 右下 右上 左下 左上
    };
    
    // 地图最大宽度 和 高度
    const int MAP_MAX_COL = 1000;
    const int MAP_MAX_ROW = 1000;
    
    const int AStarCostRightAngle = 10; // 直角移动代价
    const int AStarCostDiagonal = 14; // 斜角移动代价
    const int AStarCostWall = 80; // 城墙移动代价
    
    enum EAStarError
    {
        Error_Ok = 0, // 正确
        Error_Map = 1, // 地图错误
        Error_NotFound = 2, // 找不到
        Error_StartNotValid = 3, // 起点找不到
        Error_DestNotValid = 4, // 终点找不到
        Error_ErrorSamePoint = 5, // 同一个点
    };
    
    enum EAStarIndexType
    {
        Index_InClosed = -2, // 地图点标记-close列表中
        Index_NotUse = -1 // 地图点标记-未使用
    };
    
    enum EAStarNodeType
    {
        NodeType_Block=0, // 障碍
        NodeType_Passable=1, // 可通过
        NodeType_Wall
    };
    
    struct ANode
    {
        ANode()
        :m_iPosX(-1), m_iPosY(-1), m_iG(0), m_iH(0), m_iF(0), m_iIndex(Index_NotUse), m_pParent(nullptr)
        {
            
        }
        
        void reset()
        {
            m_iPosX = -1;
            m_iPosY = -1;
            m_iG = 0;
            m_iH = 0;
            m_iF = 0;
            m_iIndex = Index_NotUse;
            m_pParent = nullptr;
        }
        
        int m_iPosX;
        int m_iPosY;
        int m_iG;
        int m_iH;
        int m_iF;
        int m_iIndex;
        ANode* m_pParent;
    };
    
    struct PathNode
    {
        int m_iX;
        int m_iY;
    };
}

#endif /* AStarDefine_h */



















