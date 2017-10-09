//
//logo.cpp
//lvd
//create by jyx 2017.9.25
//
#include "logo.h"
#include "AppDelegate.h" 
#include "MenuScene2.h"

USING_NS_CC;

Scene* logo::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = logo::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool logo::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("menu/white.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite,0,99);//节点 99

	scheduleOnce(schedule_selector(logo::logoshowCallback), 1.0f);

	return true;

}

void logo::logoshowCallback(float temp)
{
	{
		//背景图淡入消去  
		Sprite* pSprite = (Sprite*)(getChildByTag(99));
		FadeOut* pAction = FadeOut::create(0.625f);
		pSprite->runAction(pAction);
	}

	auto pCCLayerColor = LayerColor::create(Color4B(0, 0, 0, 0));
	{
		//延迟纯黑色色背景加载0.625秒动作  
		addChild(pCCLayerColor);
		pCCLayerColor->setOpacity(0);
		DelayTime* pAction1 = DelayTime::create(0.625f);
		FadeIn* pAction2 = FadeIn::create(0.625f);
		//DelayTime* pAction3 = DelayTime::create(1.0f);  
		pCCLayerColor->runAction(Sequence::create(pAction1, pAction2, NULL));
	}

	auto s = Director::getInstance()->getVisibleSize();
	//logo的图片  
	Sprite* pSprite = Sprite::create("menu/lvd.png");
	{
		pSprite->setPosition(s.width / 2, s.height / 2);
		pCCLayerColor->addChild(pSprite);
		pSprite->setOpacity(0);
		DelayTime* pAction1 = DelayTime::create(0.625f);
		FadeIn* pAction2 = CCFadeIn::create(0.625f);
		//DelayTime* pAction3 = DelayTime::create(1.0f);  
		pSprite->runAction(Sequence::create(pAction1, pAction2, NULL));
	}

	scheduleOnce(schedule_selector(logo::logoshowOver), 2.00f);
}

void logo::logoshowOver(float temp)
{	
	//场景切换 渐变
	TransitionCrossFade* fade;
	fade = TransitionCrossFade::create(1, MenuScene2::createScene());
	Director::getInstance()->replaceScene(fade);

}
