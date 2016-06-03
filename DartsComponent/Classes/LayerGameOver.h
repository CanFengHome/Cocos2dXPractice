//
//  LayerGameOver.h
//  Darts
//
//  Created by mfp on 15/11/27.
//
//

#ifndef LayerGameOver_h
#define LayerGameOver_h

#include "cocos2d.h"

class SceneGameOver : public cocos2d::Scene
{
public:
    static SceneGameOver* createWithScore(bool isWin,int score);
private:
    bool initWithScore(bool isWin,int score);
};

class LayerGameOver : public cocos2d::LayerColor
{
public:
    static LayerGameOver* createWithScore(bool isWin,int score);
private:
    bool initWithScore(bool isWin,int score);
    
private:
    void btnBackCallback(cocos2d::Ref* pSender);
};

#endif /* LayerGameOver_h */
