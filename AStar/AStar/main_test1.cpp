////
////  main.cpp
////  AStar
////
////  Created by mfp on 16/6/12.
////  Copyright © 2016年 mfp. All rights reserved.
////
//
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//#include "AStarFindPath.h"
//using namespace AStar;
//
//const int g_col = 10;
//const int g_row = 10;
//
//unsigned char g_map[g_col*g_row];
//
//void initMap();
//void printPath(const vector<PathNode>& arrPathNodes);
//
//int g_startX = -1, g_startY = -1;
//int g_endX = -1, g_endY = -1;
//
//int main(int argc, const char * argv[])
//{
//    initMap();
//    
//    AStarFindPath findPathTool;
//    findPathTool.setMapData(g_map, g_col, g_row);
//    int pathNodeNum = 0;
//    const vector<PathNode>& arrPathNodes = findPathTool.findPath(g_startX, g_startY, g_endX, g_endY, &pathNodeNum);
//    printPath(arrPathNodes);
//    
//    return 0;
//}
//
//void initMap()
//{
//    memset(g_map, EAStarNodeType::NodeType_Passable, g_col*g_row);
//    // 1-起点  2-终点   3-障碍
//    int maze[10][10] ={{1,0,0,3,0,3,0,0,0,0},
//                       {0,0,3,0,0,3,0,3,0,3},
//                       {3,0,0,0,0,3,3,3,0,3},
//                       {3,0,3,0,0,0,0,0,0,3},
//                       {3,0,0,0,0,3,0,0,0,3},
//                       {3,0,0,3,0,0,0,3,0,3},
//                       {3,0,0,0,0,3,3,0,0,0},
//                       {0,0,2,0,0,0,0,0,0,0},
//                       {3,3,3,0,0,3,0,3,0,3},
//                       {3,0,0,0,0,3,3,3,0,3},};
//    assert(g_col == 10 && g_row == 10);
//    
//    int index = -1;
//    for (int y=0; y<g_row; ++y)
//    {
//        for (int x=0; x<g_col; ++x)
//        {
//            index = y*g_col+x;
//            if (maze[y][x] == 1)
//            {
//                g_map[index] = EAStarNodeType::NodeType_Passable;
//                g_startX = x; g_startY = y;
//            }
//            else if (maze[y][x] == 2)
//            {
//                g_map[index] = EAStarNodeType::NodeType_Passable;
//                g_endX = x; g_endY = y;
//            }
//            else if (maze[y][x] == 3)
//            {
//                g_map[index] = EAStarNodeType::NodeType_Block;
//            }
//        }
//    }
//}
//
//void printPath(const vector<PathNode>& arrPathNodes)
//{
//    if (arrPathNodes.empty())
//    {
//        cout<<"wrong! not find path"<<endl;
//    }
//    
//    cout<<"path content: "<<endl;
//    for (vector<PathNode>::const_reverse_iterator pItem = arrPathNodes.crbegin();
//         pItem != arrPathNodes.crend(); ++pItem)
//    {
//        g_map[pItem->m_iY*g_col+pItem->m_iX] = 5;
//        cout<<"->("<<pItem->m_iX<<","<<pItem->m_iY<<") ";
//    }
//    cout<<endl;
//    
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
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
