#pragma once
#include"cocos2d.h"

class Gamepause :public cocos2d::Layer
{
public :
	virtual bool init();
	static cocos2d::Scene* scene(cocos2d::RenderTexture* sqr);
	CREATE_FUNC(Gamepause);
	void menuContinueCallback(Ref* pSender);
};
