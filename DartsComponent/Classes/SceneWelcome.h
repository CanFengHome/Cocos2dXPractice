//
//  SceneWelcome.h
//  Darts
//
//  Created by mfp on 15/11/26.
//
//

#ifndef SceneWelcome_h
#define SceneWelcome_h

#include "cocos2d.h"

class LayerWelcome : public cocos2d::LayerColor
{
public:
    CREATE_FUNC(LayerWelcome);
    virtual bool init() override;
private:
    void btnStartGameCallback(cocos2d::Ref* pSender);
    void btnEndGameCallback(cocos2d::Ref* pSender);
};

class SceneWelcome : public cocos2d::Scene
{
public:
    CREATE_FUNC(SceneWelcome);
    virtual bool init() override;
};

#endif /* SceneWelcome_h */
