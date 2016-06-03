//
//  BulletController.h
//  DartsComponent
//
//  Created by ccf on 16/6/3.
//
//

#ifndef BulletController_h
#define BulletController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class BulletController : public cocostudio::ComController
{
public:
    static BulletController* createWithTouchPt(const cocos2d::Vec2& ptTouch);
    bool initWithTouchPt(const cocos2d::Vec2& ptTouch);
    virtual void onAdd() override;
private:
    cocos2d::Vec2 m_ptTouch;
};

#endif /* BulletController_h */
