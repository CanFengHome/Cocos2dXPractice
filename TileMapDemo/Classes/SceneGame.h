//
//  SceneGame.h
//  TileMapDemo
//
//  Created by ccf on 16/6/6.
//
//

#ifndef SceneGame_h
#define SceneGame_h

#include "cocos2d.h"

class SceneGame : public cocos2d::Scene
{
public:
    CREATE_FUNC(SceneGame);
    virtual bool init() override;    
};

class LayerGame : public cocos2d::Layer
{
public:
    CREATE_FUNC(LayerGame);
    virtual bool init() override;

private:
    CC_SYNTHESIZE_READONLY(cocos2d::TMXTiledMap*, m_pTiledMap, TiledMap);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, m_pPlayer, Player);
};

#endif /* SceneGame_h */
