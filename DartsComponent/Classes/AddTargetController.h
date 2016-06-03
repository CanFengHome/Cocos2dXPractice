//
//  AddTargetController.h
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#ifndef AddTargetController_h
#define AddTargetController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

// 控制场景敌人增加
class AddTargetController : public cocostudio::ComController
{
public:
    CREATE_FUNC(AddTargetController);
    virtual bool init() override;
    virtual void update(float delta) override;
private:
    void addTarget();
private:
    float m_fAddTargetTime;
    float m_fElapsedTime;
};

#endif /* AddTargetController_h */
