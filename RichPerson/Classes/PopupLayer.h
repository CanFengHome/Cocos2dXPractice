//
//  PopupLayer.h
//  RichPerson
//
//  Created by mfp on 16/5/11.
//
//

#ifndef PopupLayer_h
#define PopupLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class PopupLayer : public cocos2d::LayerColor
{
public:
    static PopupLayer* createMsgWindow(const std::string& msgTitle, const std::string& msgContent);
    static void showPopupLayer(PopupLayer* popupLyr);
    
    typedef std::function<void()> PopupLayerButtonCallback;
    
public:
    void setOkEventListener(const PopupLayerButtonCallback& okCallback);
    void setCancelEventListener(const PopupLayerButtonCallback& cancelCallback);
    
protected:
    bool initWithTitleAndContent(const std::string& msgTitle, const std::string& msgContent);
    
private:
    void btnOkCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void btnCancelCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    
private:
    PopupLayerButtonCallback m_clickOkEventListener = nullptr;
    PopupLayerButtonCallback m_clickCancelEventListener = nullptr;
};

#endif /* PopupLayer_h */
