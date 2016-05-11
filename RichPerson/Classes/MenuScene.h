//
//  MenuScene.h
//  RichPerson
//
//  Created by mfp on 16/5/10.
//
//

#ifndef MenuScene_h
#define MenuScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MenuLayer : public cocos2d::LayerColor
{
public:
    CREATE_FUNC(MenuLayer);
private:
    virtual bool init() override;
    
private:
    cocos2d::ui::Button* createNewButton(const cocos2d::ui::Widget::ccWidgetTouchCallback& callback, const cocos2d::Vec2& btnPosition, const std::string& strTitle);
    void btnSiglePersonCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnMultiplePersonCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnSoundCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnLoadGameCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnExitGameCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
};

class MenuScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(MenuScene);
private:
    virtual bool init() override;
};

#endif /* MenuScene_h */
