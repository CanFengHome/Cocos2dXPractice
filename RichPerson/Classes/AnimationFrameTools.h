//
//  AnimationFrameTools.h
//  FlappybirdDemo
//
//  Created by mfp on 15/12/19.
//
//

#ifndef AnimationFrameTools_h
#define AnimationFrameTools_h

#include <string>
#include "cocos2d.h"

class AnimationFrameTools
{
public:
    static cocos2d::Animation* createAnimation(const std::string& nameFormat, int count, float fps);
    static cocos2d::Animation* createAnimation(const std::string& actionFile, const std::string& nameFormat, int count, float fps);
    static cocos2d::Animate* createAnimation(const std::string &strFrameNameFormat, int startIndex, int endIndex, float frameDuration);
};

#endif /* AnimationFrameTools_h */
