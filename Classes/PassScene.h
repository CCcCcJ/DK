//
//  PassScene.h
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-19.
//
//
//
#ifndef __PlantsVSZombies__PassScene__
#define __PlantsVSZombies__PassScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

class PassScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(PassScene);
    void back();
    void next();
};


#endif /* defined(__PlantsVSZombies__PassScene__) */
