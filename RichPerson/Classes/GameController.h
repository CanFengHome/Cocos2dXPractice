//
//  GameController.h
//  RichPerson
//
//  Created by mfp on 16/5/17.
//
//

#ifndef GameController_h
#define GameController_h

#include "cocos2d.h"
#include "MapScene.h"

class GameController : public cocos2d::Ref
{
public:
    static GameController* createWithMapLayer(MapLayer* pMapLyr);
    bool initWithMapLayer(MapLayer* pMapLyr);
public:
    void startRolesWalking();
    
private:
    void player1WalkingFinish();
    void player2WalkingFinish();
    
private:
    MapLayer* m_pMapLyr = nullptr;
    CC_SYNTHESIZE_READONLY(int, m_iGameRoundCount, GameRoundCount);
};

#endif /* GameController_h */
