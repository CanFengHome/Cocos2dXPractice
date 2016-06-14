//
//  main_test2.cpp
//  AStar
//
//  Created by ccf on 16/6/14.
//  Copyright © 2016年 mfp. All rights reserved.
//

#include <iostream>
#include <cassert>
#include<cstdlib>
using namespace std;

#include "AStarFindPath.h"
using namespace AStar;
#include "UtilsTime.h"

const int g_col = 100;
const int g_row = 100;

unsigned char g_map[g_col*g_row];

void initMap();
void printPath(const vector<PathNode>& arrPathNodes);

int g_startX = -1, g_startY = -1;
int g_endX = -1, g_endY = -1;
int Random(int m,int n);

int main(int argc, const char * argv[])
{
    srand((int)time(NULL));
    
    initMap();
    AStarFindPath findPathTool;
    findPathTool.setMapData(g_map, g_col, g_row);
    
    int pathNodeNum = 0;
    long long startTime = UtilsTime::getTimeInMilliseconds();
    const vector<PathNode>& arrPathNodes = findPathTool.findPath(g_startX, g_startY, g_endX, g_endY, &pathNodeNum);
    long long endTime = UtilsTime::getTimeInMilliseconds();
    
    if (arrPathNodes.empty())
    {
        cout<<"第一次not found path. error "<<findPathTool.getError()<<endl<<endl;
    }
    else
    {
        printPath(arrPathNodes);
        cout<<"第一次find path ndoe num: "<<pathNodeNum<<" total time: "<<endTime-startTime<<endl<<endl;
    }
    
//    // 第二次查询
//    findPathTool.reset();
//    startTime = UtilsTime::getTimeInMilliseconds();
//    const vector<PathNode>& arrPathNodes2 = findPathTool.findPath(g_startX, g_startY, g_endX, g_endY, &pathNodeNum);
//    endTime = UtilsTime::getTimeInMilliseconds();
//    if (arrPathNodes2.empty())
//    {
//        cout<<"第二次not found path. error "<<findPathTool.getError()<<endl<<endl;
//    }
//    else
//    {
//        printPath(arrPathNodes2);
//        cout<<"第二次find path ndoe num: "<<pathNodeNum<<" total time: "<<endTime-startTime<<endl<<endl;
//    }
    
    // 第三次查询
    findPathTool.reset();
    g_startX = Random(0, g_col);
    g_startY = Random(0, g_row);
    g_endX = Random(0, g_col);
    g_endY = Random(0, g_row);
    g_map[g_startY * g_col + g_startX] = EAStarNodeType::NodeType_Passable;
    g_map[g_endY * g_col + g_endX] = EAStarNodeType::NodeType_Passable;
    
    startTime = UtilsTime::getTimeInMilliseconds();
    const vector<PathNode>& arrPathNodes3 = findPathTool.findPath(g_startX, g_startY, g_endX, g_endY, &pathNodeNum);
    endTime = UtilsTime::getTimeInMilliseconds();
    if (arrPathNodes3.empty())
    {
        cout<<"第三次not found path. error "<<findPathTool.getError()<<endl<<endl;
    }
    else
    {
        printPath(arrPathNodes3);
        cout<<"第三次find path ndoe num: "<<pathNodeNum<<" total time: "<<endTime-startTime<<endl<<endl;
    }
    
    return 0;
}

void initMap()
{
    int maxSize = g_col * g_row;
    memset(g_map, EAStarNodeType::NodeType_Passable, maxSize);
    
    int blockNum = maxSize/100;
    int currIndexX = -1;
    int currIndexY = -1;
    int index = -1;
    while (blockNum > 0)
    {
        currIndexX = Random(0, g_col);
        currIndexY = Random(0, g_row);
        index = currIndexY * g_col + currIndexX;
        if (g_map[index] == EAStarNodeType::NodeType_Block)
        {
            continue;
        }
        
        g_map[index] = EAStarNodeType::NodeType_Block;
        --blockNum;
    }
    
    g_startX = Random(0, g_col);
    g_startY = Random(0, g_row);
    g_endX = Random(0, g_col);
    g_endY = Random(0, g_row);
    g_map[g_startY * g_col + g_startX] = EAStarNodeType::NodeType_Passable;
    g_map[g_endY * g_col + g_endX] = EAStarNodeType::NodeType_Passable;
}

int Random(int m, int n)
{
    int pos, dis;
    if(m == n)
    {
        return m;
    }
    else if(m > n)
    {
        pos = n;
        dis = m - n +1;
        return rand() % dis + pos;
    }
    else
    {
        pos = m;
        dis = n - m +1;
        return rand() % dis + pos;
    }
}

void printPath(const vector<PathNode>& arrPathNodes)
{
    if (arrPathNodes.empty())
    {
        cout<<"wrong! not find path"<<endl;
    }

    cout<<"path content: "<<endl;
    for (vector<PathNode>::const_reverse_iterator pItem = arrPathNodes.crbegin();
         pItem != arrPathNodes.crend(); ++pItem)
    {
        g_map[pItem->m_iY*g_col+pItem->m_iX] = 5;
        cout<<"->("<<pItem->m_iX<<","<<pItem->m_iY<<") ";
    }
    cout<<endl;

//    g_map[g_startY*g_col+g_startX] = 6;
//    g_map[g_endY*g_col+g_endX] = 7;
//
//    int index = -1;
//    for (int y=0; y<g_row; ++y)
//    {
//        for (int x=0; x<g_col; ++x)
//        {
//            index = y*g_col+x;
//            if (g_map[index] == EAStarNodeType::NodeType_Passable)
//                cout<<0<<" ";
//            else if (g_map[index] == 6)
//                cout<<6<<" ";
//            else if (g_map[index] == 7)
//                cout<<7<<" ";
//            else if (g_map[index] == EAStarNodeType::NodeType_Block)
//                cout<<"|"<<" ";
//            else if (g_map[index] == 5)
//                cout<<5<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
}

// 结论：在1000*1000的格子中，耗时情况如下，平均在【1，2】 单位：毫秒 而一般游戏渲染引擎一致时间1s/60 = 0.016
// 一般游戏场景控制在 100*100的格子中，估计就够了，加入格子大小为32px*32px，则场景大小为3200*3200 基本耗时在[0,1]
// 另外特别注意在查询第二次数据的时候，一定要调用对应的reset接口
/*
 find path ndoe num: 804 total time: 2
 find path ndoe num: 253 total time: 0
 find path ndoe num: 253 total time: 1
 find path ndoe num: 1017 total time: 4
 find path ndoe num: 578 total time: 1
 find path ndoe num: 434 total time: 1
 find path ndoe num: 548 total time: 1
 find path ndoe num: 782 total time: 1
 find path ndoe num: 665 total time: 1
 */











