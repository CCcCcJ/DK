#ifndef __LEVELSELECT_SCENE_H__
#define __LEVELSELECT_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "PopupLayer.h"
#include "LanguageString.h"
//#include "MapChooseScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int Btn_Width1 = 222;
const int Btn_Height1 = 50;
const int Btn_FontSize1 = 20;
const int Quit_Dialog_Size_Width1 = 400;
const int Quit_Dialog_Size_Height1 = 220;
const int Level1 = 10001;
const int Level2 = 10002;
const int Level3 = 10003;
const int Level4 = 10004;
const int Level5 = 10005;
const int Btn_Quit_Cancel_TAG1 = 10006;
const int Btn_STORE_GAME_TAG1 = 10007;

class LevelSelectScene : public LayerColor
{
public:

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LevelSelectScene);

private:
	Size visibleSize;
	void menuTouchDown(Ref* pSender, Control::EventType event);
	void addBackgroundSprite();
	void addMenuSprites();
	void englishmode(int LEVEL);
	void SettingGame();
};

#endif