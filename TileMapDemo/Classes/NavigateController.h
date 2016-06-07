//
//  NavigateController.h
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#ifndef NavigateController_h
#define NavigateController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class NavigateController : public cocostudio::ComController
{
public:
    CREATE_FUNC(NavigateController);
    virtual bool init() override;
    virtual void onAdd() override;
    virtual void onEnter() override;
    virtual void update(float delta) override;
private:
    void initNavigationButton();
    void btnDirectionLeftCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnDirectionDownCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnDirectionRightCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnDirectionUpCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    
    void clickButton(const cocos2d::ui::Widget::TouchEventType& pTouchEventType);
    void startMove();
    void endMove();
private:
    float m_fOffsetX;
    float m_fOffsetY;
    float m_fMoveInternalTime;
    float m_fElapsedTime;
    cocos2d::Rect m_BoundRect;
};

#endif /* NavigateController_h */
