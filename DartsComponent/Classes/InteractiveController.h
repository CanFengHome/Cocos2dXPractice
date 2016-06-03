//
//  InteractiveController.h
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#ifndef InteractiveController_h
#define InteractiveController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class InteractiveController : public cocostudio::ComController
{
public:
    CREATE_FUNC(InteractiveController);
    virtual bool init() override;
    virtual void onAdd() override;
private:
    bool touchCallback(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void addBullet(const cocos2d::Vec2& ptTouch);
};

#endif /* InteractiveController_h */
