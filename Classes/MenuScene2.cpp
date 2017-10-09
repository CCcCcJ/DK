#include "MenuScene2.h"
#include"AudioControlScene.h"
#include "PreLoadScene.h"
#include "LevelSelect.h"
USING_NS_CC;


Scene* MenuScene2::createScene()
{
	auto scene = Scene::create();
    auto layer = MenuScene2::create();
    scene->addChild(layer);
    return scene;
	 
}
  
bool MenuScene2::init()
{
	if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	addMenuSprites();

    return true;
}

void MenuScene2::addBackgroundSprite()
{
	auto pSprite = Sprite::create("menu/bg.png");
	pSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pSprite, 0);

	auto pSprite1 = Sprite::create("menu/digit.png");
	pSprite1->setPosition(visibleSize.width / 2+150, visibleSize.height / 2);
	this->addChild(pSprite1, 0);

	auto pSprite2 = Sprite::create("menu/letter.png");
	pSprite2->setPosition(visibleSize.width / 2-150, visibleSize.height / 2);
	this->addChild(pSprite2, 0);

}


void MenuScene2:: addMenuSprites()
{	
	//路牌
	auto lupaisp = cocos2d::Sprite::create("menu/ll.png");
	lupaisp->setPosition(visibleSize.width / 2-22, visibleSize.height / 2-17);
	this->addChild(lupaisp,0);
	//英语模式
	auto btnNormal = cocos2d::extension::Scale9Sprite::create("menu/egm.png");
	ControlButton* singleGameBtn = ControlButton::create(btnNormal);

	singleGameBtn->setPosition(Vec2(visibleSize.width/2-22,visibleSize.height-122));
	singleGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene2::menuTouchDown),Control::EventType::TOUCH_UP_INSIDE);
	singleGameBtn->setTag(Btn_LOAD_GAME_TAG);
	addChild(singleGameBtn);

	//无限模式
	auto btnNormal3 = cocos2d::extension::Scale9Sprite::create("menu/utm.png");
	ControlButton* utmGameBtn = ControlButton::create(btnNormal3);

	utmGameBtn->setPosition(Vec2(visibleSize.width / 2 - 19, visibleSize.height - 174));
	utmGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene2::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	utmGameBtn->setTag(Btn_UTM_GAME_TAG);
	addChild(utmGameBtn);

	//简单模式
	auto btnNormal2 = cocos2d::extension::Scale9Sprite::create("menu/stm.png");
	ControlButton* multiGameBtn = ControlButton::create(btnNormal2);

	multiGameBtn->setPosition(Vec2(visibleSize.width/2-17,visibleSize.height-157));
	multiGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene2::menuTouchDown),Control::EventType::TOUCH_UP_INSIDE);
	multiGameBtn->setTag(Btn_START_GAME_TAG);
	addChild(multiGameBtn);

	//挑战模式
	auto btnNormal4 = cocos2d::extension::Scale9Sprite::create("menu/chm.png");
	ControlButton* chmGameBtn = ControlButton::create(btnNormal4);

	chmGameBtn->setPosition(Vec2(visibleSize.width / 2-17, visibleSize.height -222));
	chmGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene2::menuTouchDown), Control::EventType::TOUCH_UP_INSIDE);
	chmGameBtn->setTag(Btn_CHM_GAME_TAG);
	addChild(chmGameBtn);

	//选项
	auto btnNormal5 = cocos2d::extension::Scale9Sprite::create("menu/setting.png");
	ControlButton* settingsGameBtn = ControlButton::create(btnNormal5);

	settingsGameBtn->setPosition(Vec2(visibleSize.width/2-13,visibleSize.height-295));
	settingsGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene2::menuTouchDown),Control::EventType::TOUCH_UP_INSIDE);
	settingsGameBtn->setTag(Btn_SETTING_GAME_TAG);
	addChild(settingsGameBtn);


	//商店
	auto btnNormal6 = cocos2d::extension::Scale9Sprite::create("menu/help.png");
	ControlButton* loadGameBtn = ControlButton::create(btnNormal6);

	loadGameBtn->setPosition(Vec2(visibleSize.width/2-47,visibleSize.height-298));
	loadGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene2::menuTouchDown),Control::EventType::TOUCH_UP_INSIDE);
	loadGameBtn->setTag(Btn_STORE_GAME_TAG);
	addChild(loadGameBtn);
	//退出
	auto btnNormal7 = cocos2d::extension::Scale9Sprite::create("menu/quit.png");
	ControlButton* quitGameBtn = ControlButton::create(btnNormal7);

	quitGameBtn->setPosition(Vec2(visibleSize.width/2+15,visibleSize.height-275));
	quitGameBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuScene2::menuTouchDown),Control::EventType::TOUCH_UP_INSIDE);
	quitGameBtn->setTag(Btn_Quit_Game_TAG);
	addChild(quitGameBtn);

}

void MenuScene2:: menuTouchDown(Ref* pSender,Control::EventType event)
{
	ControlButton* button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case Btn_LOAD_GAME_TAG:	
		englishmode();
		break;
	case Btn_START_GAME_TAG:
		stupidmode();
		break;
	case Btn_UTM_GAME_TAG:

		break;
	case Btn_SETTING_GAME_TAG:
		SettingGame();
		break;
	case Btn_Quit_Game_TAG:
		popupQuitLayer();
		break;
	case Btn_STORE_GAME_TAG:

		break;
	default:
		break;
	}
}

void MenuScene2::popupQuitLayer(){
	PopupLayer* popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setPopModalDialog(true);
	popDialog->setContentSize(Size(Quit_Dialog_Size_Width, Quit_Dialog_Size_Height));
	popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
	popDialog->setContentText(LanguageString::getInstance()->getLanguageString(DIALOG_CONTENT)->getCString(), 20, 60, 250);
	popDialog->setCallbackFunc(this, callfuncN_selector(MenuScene2::quitButtonCallback));
	popDialog->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(OK)->getCString(), Btn_Quit_OK_TAG);
	popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Quit_Cancel_TAG);
	this->addChild(popDialog);
}

void MenuScene2::quitButtonCallback(Node *pNode)
{
	if (pNode->getTag() == Btn_Quit_OK_TAG)
	{
		Director::getInstance()->end();
	}
	else
	{
		pNode->getParent()->getParent()->removeFromParent();
	}

}
void MenuScene2::englishmode()
{
	TransitionCrossFade* fade;
		fade = TransitionCrossFade::create(1, LevelSelectScene::createScene());
	Director::getInstance()->replaceScene(fade);
}
void MenuScene2::stupidmode()
{

	TransitionCrossFade* fade = TransitionCrossFade::create(1, PreLoad::createScene(1,1));
	Director::getInstance()->replaceScene(fade);
}
void MenuScene2::SettingGame()
{
	TransitionCrossFade* fade = TransitionCrossFade::create(1, AudioControl::createScene());
	Director::getInstance()->replaceScene(fade);
}