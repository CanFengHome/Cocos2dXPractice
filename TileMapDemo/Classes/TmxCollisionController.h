//
//  TmxCollisionController.h
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#ifndef TmxCollisionController_h
#define TmxCollisionController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class TmxCollisionController : public cocostudio::ComController
{
public:
    CREATE_FUNC(TmxCollisionController);
    virtual bool init() override;
    virtual void onEnter() override;
    
    bool isCollision(const cocos2d::Vec2& position);
};

#endif /* TmxCollisionController_h */
