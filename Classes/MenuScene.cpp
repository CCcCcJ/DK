//
//  MenuScene.cpp
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-11.
//
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene2.h"
#include "AudioControlScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
	auto pSprite = Sprite::create("main_background.png");
    pSprite->setPosition(size.width/2, size.height/2);
    this->addChild(pSprite, 0);
    
	auto chengjiuImage = MenuItemImage::create("chengjiu.png", "chengjiu1.png");
    chengjiuImage->setPosition(size.width/2-100,size.height/2-50);
    
	auto imageBtn1 = MenuItemImage::create("select10.png", "select11.png",CC_CALLBACK_0(MenuScene::adventureMode,this));
  /* imageBtn1->setTarget(this, menu_selector(MenuScene::adventureMode));*/
    imageBtn1->setPosition(340, 260);
    
	auto imageBtn2 =MenuItemImage::create("select20.png", "select21.png", CC_CALLBACK_0(MenuScene::adventureMode2, this));
    imageBtn2->setPosition(340, 210);
    
	auto imageBtn3 = MenuItemImage::create("select30.png", "select31.png",CC_CALLBACK_0(MenuScene::install,this));
    imageBtn3->setPosition(340, 165);
    
    
	auto imageBtn4 =MenuItemImage::create("select40.png", "select41.png");
    imageBtn4->setPosition(330, 125);
    
	auto imageBtn5 = MenuItemImage::create("SelectorScreen_Almanac.png", "SelectorScreen_AlmanacHighlight.png");
    imageBtn5->setPosition(250, 70);
    
	auto imageBtn6 = MenuItemImage::create("shop0.png", "shop1.png");
    imageBtn6->setPosition(380, 60);
    
	auto menu = Menu::create(chengjiuImage, imageBtn1, imageBtn2, imageBtn3, imageBtn4, imageBtn5, imageBtn6, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}


//
//void MenuScene::adventureMode()
// {   CCTransitionCrossFade* fade = CCTransitionCrossFade::create(1,GameScene::scene());
//    CCDirector::sharedDirector()->replaceScene(fade);
//
//}
void MenuScene::adventureMode()
{
	/*TransitionCrossFade* fade;
	int selectLevel=UserDefault::getInstance()->getIntegerForKey("level");*/
	//if(selectLevel<=4)
	//	fade = TransitionCrossFade::create(1, GameScene2::createScene(selectLevel,));
	//else 
	//	fade = TransitionCrossFade::create(1, GameScene2::createScene(1));
	//Director::getInstance()->replaceScene(fade);

}

void MenuScene::adventureMode2()
{
	UserDefault::getInstance()->setIntegerForKey("gold", 0);
	UserDefault::getInstance()->setIntegerForKey("score",0);
	UserDefault::getInstance()->setIntegerForKey("level", 1);
	//TransitionCrossFade* fade = TransitionCrossFade::create(1, GameScene2::createScene(1));
	//Director::getInstance()->replaceScene(fade);

}
void MenuScene::install()
{
	TransitionCrossFade* fade = TransitionCrossFade::create(1, AudioControl::createScene());
	Director::getInstance()->replaceScene(fade);
}