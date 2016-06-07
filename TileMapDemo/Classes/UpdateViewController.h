//
//  UpdateViewController.h
//  TileMapDemo
//
//  Created by ccf on 16/6/7.
//
//

#ifndef UpdateViewController_h
#define UpdateViewController_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class UpdateViewController : public cocostudio::ComController
{
public:
    CREATE_FUNC(UpdateViewController);
    virtual bool init() override;
    virtual void onEnter() override;
    void updateView() const;
};

#endif /* UpdateViewController_h */
