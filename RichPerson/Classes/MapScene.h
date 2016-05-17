//
//  MapScene.h
//  RichPerson
//
//  Created by mfp on 16/5/12.
//
//

#ifndef MapScene_h
#define MapScene_h

#include <vector>
#include "cocos2d.h"
#include "MapWayData.h"
#include "ui/CocosGUI.h"
#include "RicherPlayer.h"

class GameController;
class MapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createWithMapIndex(int mapIndex);
    static MapLayer* getInstance();
    ~MapLayer();
    
    bool initWithMapIndex(int mapIndex);
    
private:
    bool addTiledMap();
    void addRightBanner();
    void drawTable(int playerNumber);
    
    void setWayPassToGrid();
    void addPlayer();
    void addGoButton();
    void addDigiteRoundSprite();
    void refreshRoundDisplay();
    
private:
    void btnGoCallback(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType pTouchEventType);
    void handlerEventRicherMsg(cocos2d::EventCustom* event);
private:
    int m_iMapIndex = -1;
    cocos2d::TMXTiledMap* m_pTiledMap = nullptr;
    cocos2d::TMXLayer* m_pWayLayer = nullptr;
    
    cocos2d::ui::Button* m_pBtnGo = nullptr;
    cocos2d::Label* m_pLblGameRound = nullptr;

    GameController* m_pGameCtrl = nullptr;
//    int m_iGameRoundCount = 0;

    std::vector<cocos2d::Vec2> m_arrWayLayerPassPosition;
    
    CC_SYNTHESIZE_READONLY(MapWayData*, m_pMapWayData, MapWayData);
    CC_SYNTHESIZE_READONLY(RicherPlayer*, m_pPlayer1, Player1);
    CC_SYNTHESIZE_READONLY(RicherPlayer*, m_pPlayer2, Player2);
};


#endif /* MapScene_h */
