//
//  AnimationFrameTools.cpp
//  FlappybirdDemo
//
//  Created by mfp on 15/12/19.
//
//

#include "AnimationFrameTools.h"

using namespace std;
USING_NS_CC;

Animation* AnimationFrameTools::createAnimation(const std::string& nameFormat, int count, float fps)
{
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(fps);
    for (int i = 0; i < count; i++)
    {
        const char *filename = __String::createWithFormat(nameFormat.c_str(),i)->getCString();
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
        animation->addSpriteFrame(frame);
    }
    return animation;
}

Animation* AnimationFrameTools::createAnimation(const std::string& actionFile, const std::string& nameFormat, int count, float fps)
{
    if (actionFile.empty() || !FileUtils::getInstance()->isFileExist(actionFile))
    {
        return nullptr;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(actionFile);
    return createAnimation(nameFormat,count,fps);
}

Animate* AnimationFrameTools::createAnimation(const string &strFrameNameFormat, int startIndex, int endIndex, float frameDuration)
{
    Animation *pAnimation = Animation::create();
    pAnimation->setDelayPerUnit(frameDuration);
    for (int i=startIndex; i<=endIndex; i++)
    {
        __String* pStrName = __String::createWithFormat(strFrameNameFormat.c_str(), i);
        SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pStrName->getCString());
        pAnimation->addSpriteFrame(pFrame);
    }
    
    assert(pAnimation != nullptr);
    return Animate::create(pAnimation);
}













