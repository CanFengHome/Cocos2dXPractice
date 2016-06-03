//
//  EnemyController.h
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#ifndef EnemyController_h
#define EnemyController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class EnemyController : public cocostudio::ComController
{
public:
    CREATE_FUNC(EnemyController);
    virtual bool init() override;
    virtual void onAdd() override;
};

#endif /* EnemyController_h */
