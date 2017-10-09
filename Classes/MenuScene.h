//
//  MenuScene.h
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-11.
//
//

#ifndef __PlantsVSZombies__MenuScene__
#define __PlantsVSZombies__MenuScene__

#include <iostream>
#include "cocos2d.h"
class MenuScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
	void adventureMode();
	void adventureMode2();
	void install();
    CREATE_FUNC(MenuScene);
	
 
};



#endif /* defined(__PlantsVSZombies__MenuScene__) */
