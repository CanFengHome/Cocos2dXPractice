//
//  PlayerController.h
//  TileMapDemo
//
//  Created by ccf on 16/6/6.
//
//

#ifndef PlayerController_h
#define PlayerController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class PlayerController : public cocostudio::ComController
{
public:
    CREATE_FUNC(PlayerController);
    virtual bool init() override;
    virtual void onAdd() override;
};

#endif /* PlayerController_h */
