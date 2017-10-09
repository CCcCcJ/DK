#ifndef __LOGO_H__
#define __LOGO_H__

#include "cocos2d.h"


class logo : public cocos2d::Layer
{
	public:
		virtual bool init();
		static cocos2d::Scene* createScene();
		void logoshowCallback(float temp);
		void logoshowOver(float temp);

		CREATE_FUNC(logo);
};
	

#endif // 
