//
//  ANodeHeap.h
//  AStar
//
//  Created by ccf on 16/6/12.
//  Copyright © 2016年 mfp. All rights reserved.
//

#ifndef ANodeHeap_h
#define ANodeHeap_h

#include "AStarDefine.h"

namespace AStar
{
    class ANodeHeap
    {
    public:
        static ANodeHeap* createWithMaxSize(int maxSize);
        bool initWithMaxSize(int maxSize);
        ~ANodeHeap();
    private:
        ANodeHeap();
        ANodeHeap(const ANodeHeap&); //拷贝构造函数不实现
        ANodeHeap& operator=(const ANodeHeap&); //赋值函数不实现
    public:
        void reset();
        bool empty() const;
        void push(ANode* pNode);
        ANode* pop();
        void sortUp(int index);
    private:
        void swap(int lhIndex, int rhIndex);
        void clear();
        void sortDown(int index);
    private:
        int m_iMaxSize;
        int m_iSize;
        ANode** m_arrNodes;
    };
}

#endif /* ANodeHeap_h */
