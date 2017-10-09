//
//  FailScene.cpp
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-19.
//
//

#include "FailScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "ConstUtil.h"
#include "LanguageString.h"
using namespace cocos2d;
using namespace CocosDenshion;

Scene* FailScene::createScene()
{
    Scene *scene = Scene::create();
    FailScene *layer = FailScene::create();
    scene->addChild(layer);
    return scene;
}

bool FailScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    Sprite* pSprite = Sprite::create("failscene.png");
    pSprite->setPosition( Vec2(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    Label* label11 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(RETURNMAINMENU)->getCString(), "Georgia-BoldItalic", 30);
    MenuItemLabel* label1 = MenuItemLabel::create(label11,CC_CALLBACK_0(FailScene::back,this));
    label1->setColor(Color3B(0, 0, 255));
    
    Label* label12 = Label::createWithSystemFont(LanguageString::getInstance()->getLanguageString(QUIT_GAME)->getCString(), "Georgia-BoldItalic", 30);
    MenuItemLabel* label2 = MenuItemLabel::create(label12,CC_CALLBACK_0(FailScene::exit,this));
    label2->setColor(Color3B(255, 0, 0));
    
    Menu* menu = Menu::create(label1, NULL);
    menu->setPosition(Vec2(140, 160));
    this->addChild(menu);
    
    Menu* menu1 = Menu::create(label2, NULL);
    menu1->setPosition(Vec2(335, 160));
    this->addChild(menu1);

    
    return true;
}

void FailScene::back()
{
    TransitionCrossFade* fade = TransitionCrossFade::create(1, MenuScene::createScene());
    Director::getInstance()->replaceScene(fade);
	GameScene2::LEVEL = 1;
}

void FailScene::exit()
{
    Director::getInstance()->end();
}
