//
//  TmxHelperController.h
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#ifndef TmxHelperController_h
#define TmxHelperController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class TmxHelperController : public cocostudio::ComController
{
public:
    CREATE_FUNC(TmxHelperController);
    virtual bool init() override;
    virtual void onEnter() override;
    
    cocos2d::Vec2 positionToTileCoord(const cocos2d::Vec2& position);
private:
    CC_SYNTHESIZE_READONLY(float, m_fMapViewWidth, MapViewWidth);
    CC_SYNTHESIZE_READONLY(float, m_fMapViewHeight, MapViewHeight);
    CC_SYNTHESIZE_READONLY(cocos2d::Size, m_mapSize, MapSize);
    CC_SYNTHESIZE_READONLY(cocos2d::Size, m_tileSize, TileSize);
};

#endif /* TmxHelperController_h */
