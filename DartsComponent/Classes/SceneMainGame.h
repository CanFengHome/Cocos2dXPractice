//
//  SceneMainGame.h
//  DartsComponent
//
//  Created by ccf on 16/6/2.
//
//

#ifndef SceneMainGame_h
#define SceneMainGame_h

#include "cocos2d.h"

class SceneMainGame : public cocos2d::Scene
{
public:
    CREATE_FUNC(SceneMainGame);
    virtual bool init() override;
};

class LayerMainGame : public cocos2d::LayerColor
{
public:
    CREATE_FUNC(LayerMainGame);
    virtual bool init() override;
    
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, m_pPlayerSprite, PlayerSprite);
};

#endif /* SceneMainGame_h */
