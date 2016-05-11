//
//  MapChooseScene.h
//  RichPerson
//
//  Created by mfp on 16/5/11.
//
//

#ifndef MapChooseScene_h
#define MapChooseScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MapChooseLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(MapChooseLayer);
private:
    virtual bool init() override;
    
private:
    void btnGoBackCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnMapCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    
private:
    cocos2d::ui::PageView* m_pPageView = nullptr;
};

class MapChooseScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(MapChooseScene);
private:
    virtual bool init() override;
};

#endif /* MapChooseScene_h */
