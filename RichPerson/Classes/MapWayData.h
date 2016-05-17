//
//  MapWayData.h
//  RichPerson
//
//  Created by mfp on 16/5/16.
//
//

#ifndef MapWayData_h
#define MapWayData_h

#include <vector>
#include "cocos2d.h"

struct GridIndex
{
public:
    GridIndex()
    {
        RowIndex = 0;
        ColIndex = 0;
    }
    
    GridIndex(int rowIndex, int colIndex)
    {
        RowIndex = rowIndex;
        ColIndex = colIndex;
    }
    
    GridIndex add(const GridIndex& rhs)
    {
        return GridIndex(RowIndex+rhs.RowIndex, ColIndex+rhs.ColIndex);
    }
    
    int RowIndex;
    int ColIndex;
};

class MapWayData : public cocos2d::Ref
{
public:
    static MapWayData* createWithRowColCount(int gridRowCount, int gridColCount);
    bool initWithRowColCount(int gridRowCount, int gridColCount);
    ~MapWayData();
    
public:
    void setGridCanPass(bool bCanPass, const GridIndex& gridIndex);
    bool getGridCanPass(const GridIndex& gridIndex) const;
    MapWayData getDataClone() const;
    void printWayData() const;
private:
    int convertGridIndexToVecotrIndex(const GridIndex& gridIndex) const;
    GridIndex convertVectorIndexToGridIndex(int vectorIndex) const;
    
private:
    std::vector<bool> m_arrCanPassGrid;
    
    CC_SYNTHESIZE_READONLY(int, m_iColCount, ColCount);
    CC_SYNTHESIZE_READONLY(int, m_iRowCount, RowCount);
    
#if _DEBUG
    bool checkGridIndex(const GridIndex& gridIndex);
#endif
};

#endif /* MapWayData_h */
