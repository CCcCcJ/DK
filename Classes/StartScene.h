//
//  StartScene.h
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-11.
//
//

#ifndef __PlantsVSZombies__StartScene__
#define __PlantsVSZombies__StartScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class StartScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
	void replaceScene();
	void removeScrollGrass(Node* sprite);
	void setMenu();

	bool flag = false;
	MenuItemFont *fontLoad;
    CREATE_FUNC(StartScene);
  
};


#endif /* defined(__PlantsVSZombies__StartScene__) */
