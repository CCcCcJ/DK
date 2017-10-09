#include "LevelSelect.h"
#include"AudioControlScene.h"
#include "PreLoadScene.h"
USING_NS_CC;


Scene* LevelSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelSelectScene::create();
	scene->addChild(layer);
	return scene;

}

bool LevelSelectScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	addMenuSprites();

	return true;
}

void LevelSelectScene::addBackgroundSprite()
{

}

void LevelSelectScene::addMenuSprites()
{
	//第一关
	auto btnNormal = cocos2d::extension::Scale9Sprite::create(NORMAL_MENU);
	auto btnPress1 = cocos2d::extension::Scale9Sprite::create(PRESS_MENU);

	Label* singleGameTTF1 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(LEVEL1)->getCString(), FONT_MENU, Btn_FontSize1);
	ControlButton* singleGameBtn1 = ControlButton::create(singleGameTTF1, btnNormal);

	singleGameBtn1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 40));
	singleGameBtn1->setPreferredSize(Size(Btn_Width1, Btn_Height1));
	singleGameBtn1->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelSelectScene::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	singleGameBtn1->setTag(Level1);
	addChild(singleGameBtn1);

	//第二关
	auto btnNorma2 = cocos2d::extension::Scale9Sprite::create(NORMAL_MENU);
	auto btnPress2 = cocos2d::extension::Scale9Sprite::create(PRESS_MENU);

	Label* singleGameTTF2 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(LEVEL2)->getCString(), FONT_MENU, Btn_FontSize1);
	ControlButton* singleGameBtn2 = ControlButton::create(singleGameTTF2, btnNorma2);

	singleGameBtn2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	singleGameBtn2->setPreferredSize(Size(Btn_Width1, Btn_Height1));
	singleGameBtn2->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelSelectScene::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	singleGameBtn2->setTag(Level2);
	addChild(singleGameBtn2);

	//第三关
	auto btnNorma3 = cocos2d::extension::Scale9Sprite::create(NORMAL_MENU);
	auto btnPress3 = cocos2d::extension::Scale9Sprite::create(PRESS_MENU);

	Label* singleGameTTF3 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(LEVEL3)->getCString(), FONT_MENU, Btn_FontSize1);
	ControlButton* singleGameBtn3 = ControlButton::create(singleGameTTF3, btnNorma3);

	singleGameBtn3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 160));
	singleGameBtn3->setPreferredSize(Size(Btn_Width1, Btn_Height1));
	singleGameBtn3->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelSelectScene::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	singleGameBtn3->setTag(Level3);
	addChild(singleGameBtn3);

	//第四关
	auto btnNorma4 = cocos2d::extension::Scale9Sprite::create(NORMAL_MENU);
	auto btnPress4 = cocos2d::extension::Scale9Sprite::create(PRESS_MENU);

	Label* singleGameTTF4 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(LEVEL4)->getCString(), FONT_MENU, Btn_FontSize1);
	ControlButton* singleGameBtn4 = ControlButton::create(singleGameTTF4, btnNorma4);

	singleGameBtn4->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 220));
	singleGameBtn4->setPreferredSize(Size(Btn_Width1, Btn_Height1));
	singleGameBtn4->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelSelectScene::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	singleGameBtn4->setTag(Level4);
	addChild(singleGameBtn4);

	//第五关
	auto btnNorma5 = cocos2d::extension::Scale9Sprite::create(NORMAL_MENU);
	auto btnPress5 = cocos2d::extension::Scale9Sprite::create(PRESS_MENU);

	Label* singleGameTTF5 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(LEVEL5)->getCString(), FONT_MENU, Btn_FontSize1);
	ControlButton* singleGameBtn5 = ControlButton::create(singleGameTTF5, btnNorma5);

	singleGameBtn5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 280));
	singleGameBtn5->setPreferredSize(Size(Btn_Width1, Btn_Height1));
	singleGameBtn5->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelSelectScene::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	singleGameBtn5->setTag(Level5);
	addChild(singleGameBtn5);
}

void LevelSelectScene::menuTouchDown(Ref* pSender, Control::EventType event)
{
	ControlButton* button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case Level1:
		englishmode(1);
		break;
	case Level2:
		englishmode(2);
		break;
	case Level3:
		englishmode(3);
		break;
	case Level4:
		englishmode(4);
		break;
	case Level5:
		englishmode(5);
	default:
		break;
	}
}


void LevelSelectScene::englishmode(int LEVEL)
{
	TransitionCrossFade* fade;
	fade = TransitionCrossFade::create(1, PreLoad::createScene(0, LEVEL));
	Director::getInstance()->replaceScene(fade);
}
void LevelSelectScene::SettingGame()
{
	TransitionCrossFade* fade = TransitionCrossFade::create(1, AudioControl::createScene());
	Director::getInstance()->replaceScene(fade);
}