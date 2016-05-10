//
//  SplashScene.h
//  RichPerson
//
//  Created by mfp on 16/5/10.
//
//

#ifndef SplashScene_h
#define SplashScene_h

#include "cocos2d.h"

class SplashLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(SplashLayer);
private:
    virtual bool init() override;
    
};

class SplashScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(SplashScene);
private:
    virtual bool init() override;
};

#endif /* SplashScene_h */
