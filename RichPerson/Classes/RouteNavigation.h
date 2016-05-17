//
//  RouteNavigation.h
//  RichPerson
//
//  Created by mfp on 16/5/17.
//
//

#ifndef RouteNavigation_h
#define RouteNavigation_h

#include <vector>
#include "MapWayData.h"

using namespace std;

enum class ENavigationDirection
{
    Up,
    Right,
    Down,
    Left
};

struct NavigationUnit
{
public:
    NavigationUnit()
    {
        
    }
    
    NavigationUnit(const GridIndex& currIndex, const GridIndex& nextIndex)
    {
        CurrGridIndex = currIndex;
        NextGridIndex = nextIndex;
    }
    
    GridIndex CurrGridIndex;
    GridIndex NextGridIndex;
};

class RicherPlayer;
class RouteNavigation
{
public:
    static vector<NavigationUnit> getMovePath(RicherPlayer* pPlayer, MapWayData* pMapWayData, int moveStep);
};

#endif /* RouteNavigation_h */
