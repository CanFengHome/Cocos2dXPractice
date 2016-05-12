//
//  MapScene.h
//  RichPerson
//
//  Created by mfp on 16/5/12.
//
//

#ifndef MapScene_h
#define MapScene_h

#include "cocos2d.h"

class MapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createWithMapIndex(int mapIndex);
    bool initWithMapIndex(int mapIndex);
    bool addTiledMap(int mapIndex);
    void addRightBanner();
    void drawTable(int playerNumber);
    void addPlayer();
    
private:
    cocos2d::TMXTiledMap* m_tiledMap = nullptr;
};


#endif /* MapScene_h */