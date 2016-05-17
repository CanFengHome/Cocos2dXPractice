//
//  RicherPlayer.cpp
//  RichPerson
//
//  Created by mfp on 16/5/16.
//
//

#include <string>

#include "RicherPlayer.h"
#include "MapSceneDefine.h"
#include "GameConvertTool.h"
#include "AnimationFrameTools.h"

using namespace std;
USING_NS_CC;

RicherPlayer* RicherPlayer::createWithPlayerType(EPlayerType playerType)
{
    RicherPlayer *pRet = new(std::nothrow) RicherPlayer();
    if (pRet && pRet->initWithPlayerType(playerType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

RicherPlayer::~RicherPlayer()
{
    CC_SAFE_RELEASE_NULL(m_pAnimatUp);
    CC_SAFE_RELEASE_NULL(m_pAnimatDown);
    CC_SAFE_RELEASE_NULL(m_pAnimatLeft);
    CC_SAFE_RELEASE_NULL(m_pAnimatRight);
}

bool RicherPlayer::initWithPlayerType(EPlayerType playerType)
{
    m_playerType = playerType;
    initPlayerSprite();
    
    return true;
}

bool RicherPlayer::initPlayerSprite()
{
    string strPlayerPListFile;
    switch (m_playerType)
    {
        case EPlayerType::Player1:
            strPlayerPListFile = PLAYER1_ANIM_PLIST;
            break;
        case EPlayerType::Player2:
            strPlayerPListFile = PLAYER2_ANIM_PLIST;
            break;
    }
    
    if (!FileUtils::getInstance()->isFileExist(strPlayerPListFile))
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(strPlayerPListFile);
    string strPlayerSpriteFrameName;
    switch (m_playerType)
    {
        case EPlayerType::Player1:
            strPlayerSpriteFrameName = "player1_anim_01.png";
            break;
        case EPlayerType::Player2:
            strPlayerSpriteFrameName = "player2_anim_01.png";
            break;
    }

    Sprite::initWithSpriteFrameName(strPlayerSpriteFrameName);
    initMoveAnimation();
    m_currDir = ENavigationDirection::Left;
    
    return true;
}

void RicherPlayer::initMoveAnimation()
{
    string strAnimationFormat;
    switch (m_playerType)
    {
        case EPlayerType::Player1:
            strAnimationFormat = "player1_anim_%02d.png";
            break;
        case EPlayerType::Player2:
            strAnimationFormat = "player2_anim_%02d.png";
            break;
    }
    
    const float playerGoPerFrameTime = 0.07f;
    m_pAnimatLeft = AnimationFrameTools::createAnimation(strAnimationFormat, 1, 4, playerGoPerFrameTime);
    m_pAnimatRight = AnimationFrameTools::createAnimation(strAnimationFormat, 5, 8, playerGoPerFrameTime);
    m_pAnimatDown = AnimationFrameTools::createAnimation(strAnimationFormat, 9, 12, playerGoPerFrameTime);
    m_pAnimatUp = AnimationFrameTools::createAnimation(strAnimationFormat, 13, 16, playerGoPerFrameTime);
    
    assert(m_pAnimatLeft != nullptr &&
           m_pAnimatRight != nullptr &&
           m_pAnimatDown != nullptr &&
           m_pAnimatUp != nullptr);
    m_pAnimatLeft->retain();
    m_pAnimatRight->retain();
    m_pAnimatDown->retain();
    m_pAnimatUp->retain();
}

void RicherPlayer::moveByRoute(const vector<NavigationUnit>& arrMovePath, NormalFunction finishCallback)
{
    if (arrMovePath.empty())
    {
        return;
    }
    
    moveOneStepByRoute(arrMovePath, finishCallback, 0);
}

void RicherPlayer::moveOneStepByRoute(const vector<NavigationUnit>& arrMovePath, NormalFunction finishCallback, int currStepIndex)
{
    if (currStepIndex >= arrMovePath.size())
    {
        if (finishCallback != nullptr)
        {
            finishCallback();
        }
        this->stopAllActions();
        return;
    }

    const float playerMoveStepTime = 0.28f;
    const NavigationUnit& pathUnit = arrMovePath[currStepIndex];
    const Vec2& nextPosition = GameConvertTool::convertGridIndexToPlayerPosition(pathUnit.NextGridIndex);
    m_currDir = GameConvertTool::calculateNavigationDir(pathUnit);
    
    Animate* pMoveAnimate = getRoleAnimateByMoveDir(m_currDir);
    assert(pMoveAnimate != nullptr);
    this->runAction(Sequence::create(Spawn::create(Repeat::create(pMoveAnimate, 1),
                                                              MoveTo::create(playerMoveStepTime, nextPosition),
                                                              nullptr),
                                                CallFunc::create(CC_CALLBACK_0(RicherPlayer::moveOneStepFinishCallback, this, arrMovePath, finishCallback, currStepIndex)),
                                                nullptr));
}

void RicherPlayer::moveOneStepFinishCallback(const vector<NavigationUnit>& arrMovePath, NormalFunction finishCallback, int currStepIndex)
{
    moveOneStepByRoute(arrMovePath, finishCallback, currStepIndex+1);
}

Animate* RicherPlayer::getRoleAnimateByMoveDir(ENavigationDirection moveDir)
{
    assert(m_pAnimatLeft != nullptr &&
           m_pAnimatRight != nullptr &&
           m_pAnimatDown != nullptr &&
           m_pAnimatUp != nullptr);
    
    switch (moveDir) {
        case ENavigationDirection::Left:
            return m_pAnimatLeft;
        case ENavigationDirection::Right:
            return m_pAnimatRight;
        case ENavigationDirection::Down:
            return m_pAnimatDown;
        case ENavigationDirection::Up:
            return m_pAnimatUp;
        default:
            return nullptr;
    }
}

























