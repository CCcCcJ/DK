//
//  FailScene.h
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-19.
//
//

#ifndef __PlantsVSZombies__FailScene__
#define __PlantsVSZombies__FailScene__

#include <iostream>
#include "cocos2d.h"
#include"GameScene2.h"
class FailScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(FailScene);
    void back();
    void exit();
};


#endif /* defined(__PlantsVSZombies__FailScene__) */
