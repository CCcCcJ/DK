//
//  PassScene.cpp
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-19.
//
//

#include "PassScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene2.h"
#include "GameScene2.h"
#include "LanguageString.h"
#include "ConstUtil.h"
using namespace cocos2d;
using namespace CocosDenshion;
using  namespace std;

Scene* PassScene::createScene()
{
    GameScene2::LEVEL++;
	UserDefault::getInstance()->setIntegerForKey("gold", GameScene2::GOLD);
	UserDefault::getInstance()->setIntegerForKey("score",GameScene2::SCORE);
	UserDefault::getInstance()->setIntegerForKey("level",GameScene2::LEVEL);
	UserDefault::getInstance()->flush();
    Scene *scene = Scene::create();
    PassScene *layer = PassScene::create();
    scene->addChild(layer);
    return scene;
}

bool PassScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
    Size size = Director::getInstance()->getWinSize();
    if( GameScene2::LEVEL > MAXLEVEL)
    {
        Sprite* pSprite = Sprite::create("trophy.png");
        pSprite->setPosition( Vec2(size.width/2, size.height/2) );
        this->addChild(pSprite, 0);
//        
        MenuItemFont* font = MenuItemFont::create(LanguageString::getInstance()->getLanguageString(RETURNMAINMENU)->getCString(),CC_CALLBACK_0(PassScene::back, this));
        font->setColor(Color3B(0, 0, 255));
//
        Menu* menu = Menu::create(font, NULL);
        menu->setPosition(Vec2(380, 50));
        this->addChild(menu);
    }
    else
    {
        Sprite* pSprite = Sprite::create("success.jpg");
        pSprite->setScale(0.5);
        pSprite->setPosition( Vec2(size.width/2, size.height/2) );
        this->addChild(pSprite, 0);
        Label* label11 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(RETURNMAINMENU)->getCString(), "Georgia-BoldItalic", 30);
        MenuItemLabel* label1 = MenuItemLabel::create(label11, CC_CALLBACK_0(PassScene::back, this));
        label1->setColor(Color3B(0, 0, 255));
        Label* label12 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(NEXTLEVEL)->getCString(), "Georgia-BoldItalic", 30);
        MenuItemLabel* label2 = MenuItemLabel::create(label12, CC_CALLBACK_0(PassScene::next, this));
        label2->setColor(Color3B(255, 0, 0));
        Menu* menu = Menu::create(label1, NULL);
        menu->setPosition(Vec2(140, 160));
        this->addChild(menu);
        Menu* menu1 = Menu::create(label2, NULL);
        menu1->setPosition(Vec2(335, 160));
        this->addChild(menu1);
    }   
    Label* label = Label::createWithSystemFont("firstgame", "Georgia-BoldItalic", 25);
    label->setPosition(Vec2(240,285));
    this->addChild(label);
    
    return true;
}
//
void PassScene::back()
{
	TransitionShrinkGrow* fade = TransitionShrinkGrow::create(1, MenuScene2::createScene());
    Director::getInstance()->replaceScene(fade);
    GameScene2::LEVEL = 1;
}
//
void PassScene::next()
{
	GameScene2::SunNumber= 50;
	TransitionShrinkGrow* fade = TransitionShrinkGrow::create(1,GameScene2::createScene(GameScene2::LEVEL,GameScene2::gamemode));
    Director::getInstance()->replaceScene(fade);
}
