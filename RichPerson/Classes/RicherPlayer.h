//
//  RicherPlayer.h
//  RichPerson
//
//  Created by mfp on 16/5/16.
//
//

#ifndef RicherPlayer_h
#define RicherPlayer_h

#include <vector>
#include "cocos2d.h"
#include "RouteNavigation.h"

enum class EPlayerType
{
    Player1,
    Player2
};

typedef std::function<void()> NormalFunction;

class RicherPlayer : public cocos2d::Sprite
{
public:
    ~RicherPlayer();
    static RicherPlayer* createWithPlayerType(EPlayerType playerType);
    bool initWithPlayerType(EPlayerType playerType);
    
    void moveByRoute(const std::vector<NavigationUnit>& arrMovePath, NormalFunction finishCallback);
    
private:
    bool initPlayerSprite();
    void initMoveAnimation();
    void moveOneStepByRoute(const vector<NavigationUnit>& arrMovePath, NormalFunction finishCallback, int currStepIndex);
    void moveOneStepFinishCallback(const vector<NavigationUnit>& arrMovePath, NormalFunction finishCallback, int currStepIndex);
    cocos2d::Animate* getRoleAnimateByMoveDir(ENavigationDirection moveDir);
private:
    cocos2d::Animate* m_pAnimatLeft = nullptr;
    cocos2d::Animate* m_pAnimatRight = nullptr;
    cocos2d::Animate* m_pAnimatUp = nullptr;
    cocos2d::Animate* m_pAnimatDown = nullptr;
    
    CC_SYNTHESIZE_READONLY(ENavigationDirection, m_currDir, CurrDir);
    CC_SYNTHESIZE_READONLY(EPlayerType, m_playerType, PlayerType);
};

#endif /* RicherPlayer_h */
