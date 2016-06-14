//
//  ANodeHeap.cpp
//  AStar
//
//  Created by ccf on 16/6/12.
//  Copyright © 2016年 mfp. All rights reserved.
//

#include "ANodeHeap.h"
#include <iostream>
#include <cassert>

namespace AStar
{
    ANodeHeap* ANodeHeap::createWithMaxSize(int maxSize)
    {
        ANodeHeap* pNodeHeap = new(std::nothrow) ANodeHeap;
        if (pNodeHeap != nullptr)
        {
            if (!pNodeHeap->initWithMaxSize(maxSize))
            {
                delete pNodeHeap;
                pNodeHeap = nullptr;
            }
        }
        
        return pNodeHeap;
    }
    
    bool ANodeHeap::initWithMaxSize(int maxSize)
    {
        if (maxSize > MAP_MAX_COL*MAP_MAX_ROW)
        {
            return false;
        }
        
        m_iMaxSize = maxSize;
        m_iSize = 0;
        m_arrNodes = new(std::nothrow) ANode*[m_iMaxSize];
        if (m_arrNodes == nullptr)
        {
            return false;
        }
        
        return true;
    }
    
    ANodeHeap::~ANodeHeap()
    {
        clear();
    }
    
    ANodeHeap::ANodeHeap()
    :m_iMaxSize(0), m_iSize(0), m_arrNodes(nullptr)
    {
        
    }
    
    void ANodeHeap::reset()
    {
        m_iSize = 0;
    }
    
    void ANodeHeap::clear()
    {
        reset();

        m_iSize = 0;
        m_iMaxSize = 0;
    }
    
    bool ANodeHeap::empty() const
    {
        return m_iSize == 0;
    }
    
    void ANodeHeap::push(ANode *pNode)
    {
        assert(m_arrNodes != nullptr && pNode != nullptr && m_iSize < m_iMaxSize);
        pNode->m_iIndex = m_iSize;
        m_arrNodes[m_iSize++] = pNode;
        // 排序
        sortUp(m_iSize-1);
    }

    void ANodeHeap::sortUp(int index)
    {
        int tmpIndex = index;
        while (tmpIndex > 0)
        {
            int parentIndex = (tmpIndex-1)/2;
            if (m_arrNodes[tmpIndex]->m_iF < m_arrNodes[parentIndex]->m_iF)
            {
                swap(parentIndex, tmpIndex);
                tmpIndex = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    void ANodeHeap::swap(int lhIndex, int rhIndex)
    {
        ANode* pTempNode = m_arrNodes[lhIndex];
        m_arrNodes[lhIndex] = m_arrNodes[rhIndex];
        m_arrNodes[lhIndex]->m_iIndex = lhIndex;
        
        m_arrNodes[rhIndex] = pTempNode;
        m_arrNodes[rhIndex]->m_iIndex = rhIndex;
    }
    
    ANode* ANodeHeap::pop()
    {
        if (empty())
        {
            return nullptr;
        }
        
        ANode* pTopNode = m_arrNodes[0];
        m_arrNodes[0] = m_arrNodes[m_iSize-1];
        --m_iSize;
        sortDown(0);
        return pTopNode;
    }
    
    void ANodeHeap::sortDown(int index)
    {
        int tmpIndex = index;
        while (tmpIndex < m_iSize)
        {
            int childLeftIndex = tmpIndex*2 + 1;
            int childRightIndex = childLeftIndex + 1;
            
            if (childLeftIndex >= m_iSize) // 不存在child，则退出循环
            {
                break;
            }
            
            if (childRightIndex >= m_iSize) // 左侧在边界
            {
                if (m_arrNodes[childLeftIndex]->m_iF >= m_arrNodes[tmpIndex]->m_iF)
                {
                    break;
                }
                else
                {
                    swap(tmpIndex, childLeftIndex);
                    break;
                }
            }
            else // 普通情况，有两个child
            {
                int swapIndex = m_arrNodes[childLeftIndex]->m_iF > m_arrNodes[childRightIndex]->m_iF?childRightIndex:childLeftIndex;
                if (m_arrNodes[swapIndex]->m_iF < m_arrNodes[tmpIndex]->m_iF)
                {
                    swap(swapIndex, tmpIndex);
                    tmpIndex = swapIndex;
                }
                else
                {
                    break;
                }
            }
        }
    }
}
















