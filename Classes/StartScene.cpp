//
//  StartScene.cpp
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-11.
//
//

#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
//#include "cocos-ext.h"

using namespace CocosDenshion;

//USING_NS_CC_EXT;

Scene* StartScene::createScene()
{
    Scene *scene = Scene::create();
    StartScene *layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    
    //添加背景
    Sprite* pSprite = Sprite::create("titlescreen.png");
    pSprite->setPosition(Vec2(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    //添加标题
    Sprite* tSprite = Sprite::create("pvz_logo.png");
    tSprite->setPosition(Vec2(size.width/2, size.height/2 + 125));
    this->addChild(tSprite);
    
    //添加草地
    Sprite* grassLandSprite = Sprite::create("down.png");
    grassLandSprite->setPosition(Vec2(size.width/2, size.height/2-120));
    this->addChild(grassLandSprite);
    
    //添加滚动草坪
    Sprite* scrollGrassSprite = Sprite::create("scrollgrass.png");
    scrollGrassSprite->setPosition(Vec2(size.width/2-150, size.height/2-70));
    RotateBy* rotateBy = RotateBy::create(5, 2*360);
    ScaleBy* scaleBy = ScaleBy::create(5, 0.5);
    Spawn* spawn = Spawn::create(rotateBy, scaleBy, NULL);	//Spawn该组合动作可以让节点同时执行多个动作
    CallFuncN* removefunc = CallFuncN::create( CC_CALLBACK_1(StartScene::removeScrollGrass,this));//CallFuncN调用还算可以传递一个参数，参数表示要调用动作的节点对象，CallFunc只是调用函数，不包括参数
    Sequence* seq = Sequence::create(spawn, removefunc, NULL);
    scrollGrassSprite->runAction(seq);
    this->addChild(scrollGrassSprite);
    
    //设置长草的效果
    MoveTo* moveTo = MoveTo::create(5, Vec2(size.width/2+145, size.height/2-82));
    Sequence* sequence = Sequence::create(moveTo, NULL);
    scrollGrassSprite->runAction(sequence);
    
    Sprite* grassSprite = Sprite::create("grass.png");
    ProgressTimer* progress = ProgressTimer::create(grassSprite);
    progress->setPosition(Vec2(size.width/2-10, size.height/2-90));
    this->addChild(progress);
    progress->setType(ProgressTimer::Type::BAR);
    ProgressFromTo* progressTo = ProgressFromTo::create(5, 0, 100);
    progress->setMidpoint(Vec2(0.0f,0.0f));
    progress->runAction(progressTo);
    
    
    //添加Loading……
    fontLoad = MenuItemFont::create("Loading......", CC_CALLBACK_0(StartScene::replaceScene, this));
 /*   fontLoad->setCallback( CC_CALLBACK_0(StartScene::replaceScene,this));*/
    fontLoad->setColor(Color3B(255, 0, 0));
    fontLoad->setFontSize(20);
    

    Menu* menu = Menu::create(fontLoad, NULL);
    menu->setPosition(Vec2(size.width/2, size.height/2-115));
    this->addChild(menu);
    
    CallFunc* func1 = CallFunc::create(CC_CALLBACK_0(StartScene::setMenu,this));
    Sequence* seq1 = Sequence::create(DelayTime::create(5), func1, NULL);
    this->runAction(seq1);
    
//    CCLabelAtlas* label1 = CCLabelAtlas::create("123456789x", "font.png", 17, 21, '0');
//    label1->setPosition(ccp(size.width/2, size.height/2));
//    //label1->setString("123");
//    this->addChild(label1);
    
    
    
    return true;
}

void StartScene::replaceScene()
{
    if (flag) {
        TransitionCrossFade* fade = TransitionCrossFade::create(1, MenuScene::createScene());
        Director::getInstance()->replaceScene(fade);
        
    }
    else
    {
        log("mei dao shi jian");
    }
    
}

void StartScene::removeScrollGrass(Node* sprite)
{
    sprite->removeFromParent();
}

void StartScene::setMenu()
{
    flag = true;
    __String* string = __String::create("start game");
    fontLoad->setString(string->getCString());
	/*fontLoad->setString("start game");*/
}

