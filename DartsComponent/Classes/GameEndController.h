//
//  GameEndController.h
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#ifndef GameEndController_h
#define GameEndController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class GameEndController : public cocostudio::ComController
{
public:
    CREATE_FUNC(GameEndController);
    virtual bool init() override;
    virtual void onAdd() override;
    
    void targetMoveFinished();
    bool contactCallback(cocos2d::PhysicsContact& contact);
private:
    int m_iKillCount;
};

#endif /* GameEndController_h */
