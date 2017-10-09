//
//  GameScene.cpp
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-12.
//
//
#include"time.h"
#include"random"
#include "StartScene.h"
#include "GameScene2.h"
#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
#include "hero.h"
#include "SimpleAudioEngine.h"
//#include "Data.h"
#include "Bullet.h"
#include "PassScene.h"
#include "FailScene.h"
//#include"sqlite3\include\sqlite3.h"
#include "PreLoadScene.h"
#include"string.h"
#include"Loadskeletondata.h"
#include"gamepause.h"
#include"readleveldata.h"
using namespace spine;
using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;
//USING_NS_CC;
Vector<Sprite*> GameScene2::bulletArray;//子弹数组
int GameScene2::SunNumber = 0;
int GameScene2::LEVEL = 1;
int GameScene2::SCORE = 0;
int GameScene2::GOLD = 0;
int GameScene2::gamemode = 0;
Scene* GameScene2::createScene(int selectLevel, int type)
{
	//将数据以UserDefault方式保存
	gamemode = type;
	GOLD = UserDefault::getInstance()->getIntegerForKey("gold");
	SCORE = UserDefault::getInstance()->getIntegerForKey("score");
	LEVEL = selectLevel;
	Scene *scene = Scene::create();
	GameScene2 *layer = GameScene2::create();
	scene->addChild(layer);
	return scene;
}
void GameScene2::onEnter()
{
	Layer::onEnter();
	/*SimpleAudioEngine::getInstance()->playBackgroundMusic("s3.wav", true);*/
}

bool GameScene2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	//暂停按键
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene2::menuPauseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	//把当前时间作为随机数的种子
	srand(time(NULL)); // set random seed
	//获得阳光的帧动画
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Sun_default.plist");
    //加入菜单框
	menuSprite = Sprite::create("SeedChooser_Background.png");
	menuSprite->setPosition(Vec2(170, 120));
	this->addChild(menuSprite, 1);

	auto leveldata = readleveldata::create(LEVEL);
	//// rapidjson对象
	//rapidjson::Document document;
	///*关卡数据使用json，Cocos2d-X 3.0中自带了rapidjson，用于解析Json。
	// 根据传递的关卡值解析对应的关卡数据文件*/
	//std::string filePath = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("%d.data", LEVEL));
	//std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
	//document.Parse<0>(contentStr.c_str());
	////获得背景图的名称
	//std::string BackGround = document["background"].GetString();
	//读取瓦片地图
	_map = TMXTiledMap::create(leveldata->get_background());
	_map->setAnchorPoint(Vec2(0.5, 0.5));
	//分配瓦片地图中种植的数组的空间
	_mapSizewidth = _map->getMapSize().width;
	_mapSizeheigh = _map->getMapSize().height;
	canPlantGrid = new PlantFlag*[_mapSizewidth];
	for (int i=0; i < _map->getMapSize().width; i++)
		canPlantGrid[i] = new PlantFlag[_mapSizeheigh];
	//初始化数组
	this->initFlag();
	//适配保证背景图片的最左边可以显示
	auto pSpritesize = _map->getBoundingBox().size;
	if (visibleSize.width>pSpritesize.width)
		_map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	else
		_map->setPosition(Vec2(pSpritesize.width / 2, visibleSize.height / 2));
	this->addChild(_map, 0);


	//读出每关怪兽出现的数量
	_monsterDatas = leveldata->get_monsterDatas();
	_menuDatas = leveldata->get_menuDatas();
	monster_number = leveldata->getmonster_number();
	//monster_number = document["number"].GetInt();
	//const rapidjson::Value& monster_Array = document["monsters"];
	////读出一关中出现的怪物的种类并存入Vector容器中
	//for (unsigned int i = 0; i < monster_Array.Size(); i++)
	//{
	//	std::string name = monster_Array[i]["name"].GetString();
	//	auto monsterData = MonsterData::create();
	//	monsterData->setmonstertype(name);
	//	_monsterDatas.pushBack(monsterData);
	//}
	//const rapidjson::Value& menu_Array = document["menu"];
	////模拟拥有的英雄，将拥有的英雄数据存入UserDefault中
	//UserDefault::getInstance()->setBoolForKey("CherryBomb.png", true);
	//UserDefault::getInstance()->setBoolForKey("Chomper.png", true);
	//UserDefault::getInstance()->setBoolForKey("Jalapeno.png", true);
	//UserDefault::getInstance()->setBoolForKey("LilyPad.png", true);
	//UserDefault::getInstance()->setBoolForKey("PeaShooter.png", true);
	//UserDefault::getInstance()->setBoolForKey("Repeater.png", true);
	//UserDefault::getInstance()->setBoolForKey("SunFlower.png", true);
	//UserDefault::getInstance()->setBoolForKey("TallNut.png", true);
	////读出一关中可选参与战斗的英雄，并存入Vector容器中
	//for (unsigned int i = 0; i < menu_Array.Size(); i++)
	//{
	//	int menutag = menu_Array[i]["menutag"].GetInt();
	//	auto menuData = MenuData::create();
 //       //读取文件中的菜单的tag
	//	menuData->setmenu_member(menutag);
	//	_menuDatas.pushBack(menuData);
	//}
	//添加菜单
	this->addMenu();
	//菜单条的创建
	barMenuSprite = Sprite::create("barMenu1.png");
	barMenuSprite->setScaleX(1.2f);
	barMenuSprite->setScaleY(1.4f);
	barMenuSprite->setPosition(Vec2(140, 295));
	this->addChild(barMenuSprite, 1);
	//移动主菜单
	//MoveTo* moveToMenu = MoveTo::create(2, Vec2(170, 120));
	//Sequence* seq2 = Sequence::create(DelayTime::create(2), moveToMenu, NULL);
	//menuSprite->runAction(seq2);

	//添加太阳图标
	Sprite* sun2Sprite = Sprite::create("sun2.png");
	sun2Sprite->setPosition(Vec2(35, 30));
	sun2Sprite->setScaleY(0.8f);
	sun2Sprite->setScaleX(0.9f);
	barMenuSprite->addChild(sun2Sprite);
	//添加太阳显示图标
	Sprite* sunNumSprite = Sprite::create("sunNum.png");
	sunNumSprite->setPosition(Vec2(35, 10));
	sunNumSprite->setScaleY(0.5);
	barMenuSprite->addChild(sunNumSprite, 2);

	//初始化太阳的个数
	SunNumber = 3000;
	sunNumberLB = Label::createWithSystemFont("50", "Verdana-Bold", 15);
	sunNumberLB->setPosition(Vec2(20, 10));
	sunNumberLB->setScaleY(1.4f);
	sunNumberLB->setColor(Color3B(0, 0, 255));
	sunNumSprite->addChild(sunNumberLB, 2);
	if (gamemode == 0)
	{
		//初始化显示单词标签
		wordLB = Label::createWithSystemFont("         ", "Verdana-Bold", 15);
		wordLB->setScaleY(1.5f);
		wordLB->enableShadow(Color4B::BLUE, Size(1, 1));
		wordLB->enableOutline(Color4B::BLACK, 1);
		wordLabel = MenuItemLabel::create(wordLB, CC_CALLBACK_1(GameScene2::readword, this));
		wordmenu = Menu::create(wordLabel, NULL);
		wordmenu->setPosition(Vec2(350, 110));
		this->addChild(wordmenu);
		//中文选项菜单A,B,C
		ChineseLB_A = Label::createWithSystemFont("     ", "Verdana-Bold", 12);//设置选项标签
		ChineseLB_A->setScaleY(1.5f);
		ChineseLB_A->setColor(Color3B(255, 255, 255));
		ChineseLB_A->enableShadow(Color4B::GRAY, Size(1, 1));//设置文字阴影
		ChineseLB_A->enableOutline(Color4B::BLUE, 1);//第一个参数为描边的颜色，第二个参数为描边的大小  
		MenuItemLabel* ChineseLabel = MenuItemLabel::create(ChineseLB_A, CC_CALLBACK_1(GameScene2::Judge, this));//点击选项判断正确与否
		ChineseLabel->setTag(0);
		ChineseLB_B = Label::createWithSystemFont("     ", "Verdana-Bold", 12);
		ChineseLB_B->setScaleY(1.5f);
		ChineseLB_B->setColor(Color3B(255, 255, 255));
		ChineseLB_B->enableShadow(Color4B::BLUE, Size(1, 1));
		ChineseLB_B->enableOutline(Color4B::RED, 1);
		MenuItemLabel* ChineseLabel2 = MenuItemLabel::create(ChineseLB_B, CC_CALLBACK_1(GameScene2::Judge, this));
		ChineseLabel2->setTag(1);
		ChineseLB_C = Label::createWithSystemFont("     ", "Verdana-Bold", 12);
		ChineseLB_C->setScaleY(1.5f);
		ChineseLB_C->setColor(Color3B(255, 255, 255));
		ChineseLB_C->enableShadow(Color4B::MAGENTA, Size(1, 1));
		ChineseLB_C->enableOutline(Color4B::BLUE, 1);
		MenuItemLabel* ChineseLabel3 = MenuItemLabel::create(ChineseLB_C, CC_CALLBACK_1(GameScene2::Judge, this));
		ChineseLabel3->setTag(2);
		chinesemenu = Menu::create(ChineseLabel, ChineseLabel2, ChineseLabel3, NULL);
		chinesemenu->alignItemsVerticallyWithPadding(20);
		chinesemenu->setPosition(Vec2(350, 50));
		chinesemenu->setTag(300);
		this->addChild(chinesemenu);
	}
	//注册触摸代理
	//Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene2::touchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene2::touchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene2::touchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//时间调度
	EventDispatcher * eventDispatcher = Director::getInstance()->getEventDispatcher();
	this->schedule(schedule_selector(GameScene2::setSunNumberLB), 0.1f);//改阳光的值
	this->schedule(schedule_selector(GameScene2::createHeroShoote), 0.6f);//英雄产生子弹
	plantsIsPlanted = true;
	this->LevelBar();
	//关卡显示
	Label* labelLevel = Label::createWithSystemFont(" ", "TrebuchetMS", 20);
	char label[20];
	sprintf(label, "level:%d", LEVEL);
	labelLevel->setPosition(Vec2(420, 300));
	labelLevel->setColor(Color3B(255, 255, 0));
	this->addChild(labelLevel);
	labelLevel->setString(label);
	//分数显示
	labelScore = Label::createWithSystemFont(" ", "TrebuchetMS", 20);
	char label2[20];
	sprintf(label2, "score:%d", SCORE);
	labelScore->setPosition(Vec2(420, 280));
	labelScore->setColor(Color3B(255, 255, 0));
	this->addChild(labelScore);
	labelScore->setString(label2);
	//金币显示
	auto gold = Sprite::create("gold.png");
	gold->setPosition(410, visibleSize.height*0.8);
	this->addChild(gold, 2);
	char gold_number[20];
	sprintf(gold_number, "%d", GOLD);
	_goldLabel = Label::createWithSystemFont(" ", "Arial", 20);
	_goldLabel->setColor(Color3B::YELLOW);
	_goldLabel->setString(gold_number);
	_goldLabel->setPosition(450, visibleSize.height*0.8);
	this->addChild(_goldLabel, 2);
	return true;
}
void GameScene2::menuPauseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	//    Director::getInstance()->end();
	//
	//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//    exit(0);
	//#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);



	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。  
	//这里类似截图。  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面  
	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));

}
void GameScene2::readword(Ref* pSender)
{
	char ch[60];
	sprintf(ch, "pronunciation/%s.mp3", answer);
	SimpleAudioEngine::getInstance()->playEffect(ch);
}
void GameScene2::Judge(Ref* pSender)
{
	char gold_number[20];
	int option = ((MenuItemLabel*)pSender)->getTag();
	if (option == answer_tag)
	{
		GOLD += 1;
		//log(G2U("正确"));
		sprintf(gold_number, "%d", GOLD);
		_goldLabel->setString(gold_number);
	}
	/*else
	log(G2U("错误"));*/

}
void GameScene2::setword(float dt)
{

	char string1[60];
	char string2[60];
	char string3[60];
	//char string4[3][60];
	//int i ;
	int count = CCRANDOM_0_1() * 2546 + 1;
	int count2;
	int count3;
	count2 = CCRANDOM_0_1() * 2 + 2;//取[2-4）
	count3 = CCRANDOM_0_1() * 2 + 4;//取[4-6)
	int index = count * 7;
	sprintf(answer, "%s", PreLoad::result[index]);
	int random0_2 = CCRANDOM_0_1() * 3;
	if (random0_2 == 0)//正确答案随机放置
	{
		answer_tag = 0;
		sprintf(string1, "A:%s", PreLoad::result[index + 1]);//取正确选项
		sprintf(string2, "B:%s", PreLoad::result[index + count2]);//取错误选项
		sprintf(string3, "C:%s", PreLoad::result[index + count3]);
	}
	else if (random0_2 == 1)
	{
		answer_tag = 1;
		sprintf(string1, "A:%s", PreLoad::result[index + count2]);
		sprintf(string2, "B:%s", PreLoad::result[index + 1]);
		sprintf(string3, "C:%s", PreLoad::result[index + count3]);
	}
	else
	{
		answer_tag = 2;
		sprintf(string1, "A:%s", PreLoad::result[index + count3]);
		sprintf(string2, "B:%s", PreLoad::result[index + count2]);
		sprintf(string3, "C:%s", PreLoad::result[index + 1]);
	}
	wordLB->setString(PreLoad::result[index]);//更改单词文本框单词
	ChineseLB_A->setString(string1);//更改选项文本框单词
	ChineseLB_B->setString(string2);
	ChineseLB_C->setString(string3);
	log("%s", PreLoad::result[index + 1]);
}
void GameScene2::setSunNumberLB(float dt)
{
	sprintf(sunNum, "%d", SunNumber);
	sunNumberLB->setString(sunNum);
}

void GameScene2::removeSprite(cocos2d::Node *sprite)
{
	sprite->removeFromParent();
}
//选择本关菜单中的英雄
void GameScene2::plantsMenu(Ref* Object)
{

	Node* object = (Node*)Object;
	int plantsTag = object->getTag();
	MenuItemToggle* plantsToggle = (MenuItemToggle*)object;
	Sprite* cherry;
	Sprite* chomper;
	Sprite* jalapeno;
	Sprite* lilypad;
	Sprite* peashooter;
	Sprite* repeater;
	Sprite* squash;
	Sprite* sunflower;
	Sprite* tallnut;
	Sprite* threepeater;
	Sprite* wallnut;
	if (plantsMenuArray.size() < 6) {
		switch (plantsTag) {
		case CHERRY:
			cherry = Sprite::create("rolecard/heroa.png");//菜单选择使用的角色后生成的精灵,临时精灵。
			cherry->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			cherry->setScale(0.35f);
			plantsSpriteArray.pushBack(cherry);
			cherry->setTag(501);
			this->addChild(cherry, 1);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case CHOMPER:
			chomper = Sprite::create("rolecard/herob.png");
			chomper->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			chomper->setScale(0.35f);
			plantsSpriteArray.pushBack(chomper);
			chomper->setTag(502);
			this->addChild(chomper, 1);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case JALAPENO:
			jalapeno = Sprite::create("rolecard/heroc.png");
			jalapeno->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			jalapeno->setScale(0.35f);
			plantsSpriteArray.pushBack(jalapeno);
			jalapeno->setTag(503);
			this->addChild(jalapeno, 1);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case LILYPAD:
			lilypad = Sprite::create("rolecard/herod.png");
			lilypad->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			lilypad->setScale(0.35f);
			plantsSpriteArray.pushBack(lilypad);
			lilypad->setTag(504);
			this->addChild(lilypad, 1);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case PEASHOOTER:
			peashooter = Sprite::create("rolecard/heroo.png");
			peashooter->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			peashooter->setScale(0.35f);
			plantsSpriteArray.pushBack(peashooter);
			peashooter->setTag(505);
			this->addChild(peashooter, 1);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case REPEATER:
			repeater = Sprite::create("rolecard/herou.png");
			repeater->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			repeater->setScale(0.35f);
			plantsSpriteArray.pushBack(repeater);
			repeater->setTag(506);
			this->addChild(repeater, 1);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case SQUASH:
			squash = Sprite::create("rolecard/heroi.png");
			squash->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			squash->setScale(0.35f);
			plantsSpriteArray.pushBack(squash);
			squash->setTag(507);
			this->addChild(squash, 2);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case SUNFLOWER:
			sunflower = Sprite::create("rolecard/herou.png");
			sunflower->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			sunflower->setScale(0.35f);
			plantsSpriteArray.pushBack(sunflower);
			sunflower->setTag(508);
			this->addChild(sunflower, 2);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case TALLNUA:
			tallnut = Sprite::create("rolecard/herou.png");
			tallnut->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			tallnut->setScale(0.35f);
			plantsSpriteArray.pushBack(tallnut);
			tallnut->setTag(509);
			this->addChild(tallnut, 2);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case THREEPEATER:
			threepeater = Sprite::create("rolecard/herou.png");
			threepeater->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			threepeater->setScale(0.35f);
			plantsSpriteArray.pushBack(threepeater);
			threepeater->setTag(510);
			this->addChild(threepeater, 2);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		case WALLNUA:
			wallnut = Sprite::create("rolecard/herou.png");
			wallnut->setPosition(plantsToggle->getParent()->convertToWorldSpace(plantsToggle->getPosition()));
			wallnut->setScale(0.35f);
			plantsSpriteArray.pushBack(wallnut);
			wallnut->setTag(511);
			this->addChild(wallnut, 2);
			plantsToggle->setEnabled(false);//菜单按钮不可用
			break;
		default:
			break;
		}

	}
	if (plantsMenuArray.size() < 6)
	{
		MenuItemToggle* toggleItem;
		if (plantsTag >= 101 && plantsTag <= 111)
		{
			switch (plantsTag) {
			case CHERRY:
				toggleItem = this->createMenuItem1("rolecard/heroa.png", "rolecard/heroaNOT.png", 201);//选择种植的图标后生成的每关固定的种植图标
				toggleItem->setScale(0.7f);
				break;
			case CHOMPER:
				toggleItem = this->createMenuItem1("rolecard/herob.png", "rolecard/herobNOT.png", 202);
				toggleItem->setScale(0.7f);
				break;
			case JALAPENO:
				toggleItem = this->createMenuItem1("rolecard/heroc.png", "rolecard/herocNOT.png", 203);
				toggleItem->setScale(0.7f);
				break;
			case LILYPAD:
				toggleItem = this->createMenuItem1("rolecard/herod.png", "rolecard/herodNOT.png", 204);
				toggleItem->setScale(0.7f);
				break;
			case PEASHOOTER:
				toggleItem = this->createMenuItem1("rolecard/heroo.png", "rolecard/herooNOT.png", 205);
				toggleItem->setScale(0.7f);
				break;
			case REPEATER:
				toggleItem = this->createMenuItem1("rolecard/herou.png", "rolecard/herouNOT.png", 206);
				toggleItem->setScale(0.7f);
				break;
			case SQUASH:
				toggleItem = this->createMenuItem1("rolecard/heroi.png", "rolecard/heroiNOT.png", 207);
				toggleItem->setScale(0.7f);
				break;
			case SUNFLOWER:
				toggleItem = this->createMenuItem1("rolecard/herou.png", "rolecard/herouNOT.png", 208);
				toggleItem->setScale(0.7f);
				break;
			case TALLNUA:
				toggleItem = this->createMenuItem1("rolecard/herou.png", "rolecard/herouNOT.png", 209);
				toggleItem->setScale(0.7f);
				break;
			case THREEPEATER:
				toggleItem = this->createMenuItem1("rolecard/herou.png", "rolecard/herouNOT.png", 210);
				toggleItem->setScale(0.7f);
				break;
			case WALLNUA:
				toggleItem = this->createMenuItem1("rolecard/herou.png", "rolecard/herouNOT.png", 211);
				toggleItem->setScale(0.7f);
				break;
			default:
				break;
			}
			toggleItem->setPosition(Vec2(80+plantsMenuArray.size()*40, 0));
			plantsMenuArray.pushBack(toggleItem);
			for (int i = 1; i < 7; i++)
			{
				if (plantsMenuArray.size() == i)
				{
					Sprite* sprite = (Sprite*)plantsSpriteArray.at(i - 1);
					JumpTo* jumpTo = JumpTo::create(0.7f, Vec2(80 + (i - 1) * 40, 300), 70, 1);//设置英雄卡片的位置
					sprite->runAction(jumpTo);
					plantsToggle->setTag(plantsTag + 100);//...
				}
			}
			if (plantsMenuArray.size() == 6)//选6个所有图标禁止
			{
				for (int i = 101; i < 107; i++)
				{
					MenuItemToggle* banmenuSprite1 = (MenuItemToggle*)menuSprite->getChildByTag(601)->getChildByTag(i);
					if (banmenuSprite1 != NULL)
					{
						banmenuSprite1->setEnabled(false);
						banmenuSprite1->setSelectedIndex(1);
					}
					for (int i = 107; i < 112; i++)
					{
						MenuItemToggle* banmenuSprite1 = (MenuItemToggle*)menuSprite->getChildByTag(602)->getChildByTag(i);
						if (banmenuSprite1 != NULL)
						{
							banmenuSprite1->setEnabled(false);
							banmenuSprite1->setSelectedIndex(1);
						}
					}


				}
			}
		}

	}
}
void GameScene2::plantingPlant(cocos2d::Ref *Object)
{
	Node* plant = (Node*)Object;
	MenuItemToggle* plantToggle = (MenuItemToggle*)plant;
	int plantsTag = plant->getTag();
	/*   Plants* thePlant;*/
	hero* Hero;
	switch (plantsTag) {
	case CHERRY + 100:
		SunNumber -= 150;
		cherryCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);//控制按钮是否可用

		Hero = new hero(hero1);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case CHOMPER + 100:
		SunNumber -= 150;
		chomperCoolTime = 7;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);

		Hero = new hero(hero2);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case JALAPENO + 100:
		SunNumber -= 125;
		jalapenoCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		Hero = new hero(hero3);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case LILYPAD + 100:
		SunNumber -= 25;
		lilypadCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		Hero = new hero(hero4);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case PEASHOOTER + 100:
		SunNumber -= 100;
		peashooterCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);

		//  thePlant->setPosition(Vec2(0, -100));//解决在点击菜单后，没有种植时，子弹从Vec2(0,0)位置飞出的情况
		Hero = new hero(hero5);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case REPEATER + 100:
		SunNumber -= 200;
		repeaterCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);

		//thePlant->setPosition(Vec2(0, -100));//解决在点击菜单后，没有种植时，子弹从Vec2(0,0)位置飞出的情况
		Hero = new hero(hero6);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case SQUASH + 100:
		SunNumber -= 50;
		squashCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		Hero = new hero(hero7);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case SUNFLOWER + 100:
		SunNumber -= 50;
		sunflowerCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		//thePlant->setPosition(Vec2(0, -100));//解决在点击菜单后，没有种植时，子弹从Vec2(0,0)位置飞出的情况
		Hero = new hero(hero1);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case TALLNUA + 100:
		SunNumber -= 125;
		tallnutCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		Hero = new hero(hero3);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case THREEPEATER + 100:
		SunNumber -= 325;
		threepeaterCoolTime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		//thePlant->setPosition(Vec2(0, -100));//解决在点击菜单后，没有种植时，子弹从Vec2(0,0)位置飞出的情况
		Hero = new hero(hero3);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	case WALLNUA + 100:
		SunNumber -= 50;
		wallnutCooltime = 5;
		plantToggle->setSelectedIndex(1);
		plantToggle->setEnabled(false);
		Hero = new hero(hero3);
		heroArray.pushBack(Hero);
		plantsIsPlanted = false;
		break;
	default:
		break;
	}

}

void GameScene2::menuItemToggle(Ref* pSender)
{
	log("selectedindex:%d", dynamic_cast<MenuItemToggle*>(pSender)->getSelectedIndex());

}
MenuItemToggle* GameScene2::createMenuItem(const char* plantName1, const char* plantName2, int tag)
{
	MenuItemImage* image = MenuItemImage::create(plantName1, plantName1);
	image->setScale(0.5);
	MenuItemImage* image1 = MenuItemImage::create(plantName2, plantName2);
	image1->setScale(0.5);
	/*  auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScene2::menuItemToggle,this), image,image1, NULL);*/
	/*  CCMenuItemToggle* toggle = CCMenuItemToggle::createWithTarget(this, menu_selector(GameScene::plantsMenu), image, image1, NULL);*/
	auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScene2::plantsMenu, this), image, image1, NULL);
	toggle->setTag(tag);
	return toggle;
}
//
MenuItemToggle* GameScene2::createMenuItem1(const char* plantName1, const char* plantName2, int tag)
{
	MenuItemImage* image = MenuItemImage::create(plantName1, plantName1);
	image->setScale(0.5f);
	MenuItemImage* image1 = MenuItemImage::create(plantName2, plantName2);
	image1->setScale(0.5f);
	MenuItemToggle* toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScene2::plantingPlant, this), image, image1, NULL);
	toggle->setTag(tag);
	return toggle;
}

void GameScene2::moveScenePosition()
{

	MoveTo* moveTo = MoveTo::create(2, Vec2(270, 160));
	_map->runAction(moveTo);
}

void GameScene2::sunAction()
{
	//阳光
	Sprite* sunSprite = Sprite::createWithSpriteFrameName("Sun1.tiff");
	sunSprite->setPosition(Vec2(240, 160));
	sunSprite->setScale(0.5f);
	this->addChild(sunSprite);
	/*   CCArray* sunArray = CCArray::create();
	sunArray->retain();*/
	Vector<SpriteFrame*> sunArray(25);
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	char name[50];
	for (int i = 1; i<23; i++)
	{
		sprintf(name, "Sun－%i.tiff", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(name);
		sunArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(sunArray, 0.3f);
	Animate* animate = Animate::create(animation);
	sunSprite->runAction(CCRepeatForever::create(animate));
	/*   sunArray->release();*/
}

void GameScene2::addMenu()
{
	MenuItemToggle* toggleCherry;
	for (int i = 0; i < _menuDatas.size(); i++)
	{
		if (i >= 6)//6个为一排
			break;
		auto menu_temp = _menuDatas.at(i);
		toggleCherry = this->createMenuItem(menu_temp->getmember_name1().c_str(), menu_temp->getmenber_name2().c_str(), menu_temp->gettag());
		//if (!menu_temp->getavailability())//判断是否购买了这英雄
		//{
		//	toggleCherry->setEnabled(false);
		//	toggleCherry->setSelectedIndex(1);
		//}
		toggleCherry->setScale(0.7f);
		toggleCherry->setPosition(Vec2(i*35 + 10 * i,0));
		Menutemp_Array1.pushBack(toggleCherry);
	}
	for (int i = 6; i < _menuDatas.size(); i++)
	{
		auto menu_temp = _menuDatas.at(i);
		toggleCherry = this->createMenuItem(menu_temp->getmember_name1().c_str(), menu_temp->getmenber_name2().c_str(), menu_temp->gettag());
	/*	if (!menu_temp->getavailability())
		{
			toggleCherry->setEnabled(false);
			toggleCherry->setSelectedIndex(1);
		}*/
		toggleCherry->setPosition(Vec2((i - 6)*35 + 10 * (i - 6),0));
		toggleCherry->setScale(0.7f);
		Menutemp_Array2.pushBack(toggleCherry);
		
	}
	//添加重置按钮
	auto selectReset = MenuItemImage::create("selectReset0.png", "selectReset1.png", CC_CALLBACK_0(GameScene2::resetBarMenu, this));

	//添加确定按钮
	auto selectSure = MenuItemImage::create("selectSure0.png", "selectSure1.png", CC_CALLBACK_0(GameScene2::beSure, this));
	selectSure->setTag(33);
	Menu* menu1 = Menu::createWithArray(Menutemp_Array1);
	menu1->setPosition(Vec2(40, 190));
	//menu1->alignItemsHorizontallyWithPadding(-20);
	menu1->setTag(601);
	menuSprite->addChild(menu1, 20);
	/*  Menu* menu2 = Menu::create(toggleSquash, toggleSunFlower, toggleTallNut, toggleThreepeater, toggleWallNut, NULL);*/
	Menu* menu2 = Menu::createWithArray(Menutemp_Array2);
	menu2->setPosition(Vec2(40, 120));
	//menu2->alignItemsHorizontallyWithPadding(-20);
	menu2->setTag(602);
	menuSprite->addChild(menu2);
	Menu* menu3 = Menu::create(selectReset, selectSure, NULL);
	menu3->setPosition(Vec2(170, 50));
	menu3->alignItemsHorizontallyWithPadding(-20);
	menu3->setTag(603);
	menuSprite->addChild(menu3);
}

void GameScene2::resetBarMenu()
{
	plantsMenuArray.clear();
	plantsSpriteArray.clear();
	Menutemp_Array1.clear();
	Menutemp_Array2.clear();
	menuSprite->removeChildByTag(601);
	menuSprite->removeChildByTag(602);
	menuSprite->removeChildByTag(603);
	this->addMenu();
	for (int i = 501; i<512; i++) {
		this->removeChildByTag(i);
	}
}
//
void GameScene2::beSure()
{
	((MenuItemImage*)menuSprite->getChildByTag(603)->getChildByTag(33))->setEnabled(false);
	Size size = Director::getInstance()->getWinSize();
	for (int i = 501; i<512; i++) {//删除选择图标后的移动到菜单的图标
		this->removeChildByTag(i);
	}

	Menu* menu = Menu::createWithArray(plantsMenuArray);
	menu->setPosition(Vec2(0, 300));
	//menu->alignItemsHorizontallyWithPadding(-20);//水平方向间隙排列设置
	this->addChild(menu, 2);

	//添加准备安放植物字体
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("PrepareGrowPlants_default.plist");
	Sprite* fontSprite = Sprite::createWithSpriteFrameName("PrepareGrowPlants1.tiff");
	fontSprite->setPosition(Vec2(240, 160));
	this->addChild(fontSprite);
	char fontName[30];
	Vector<SpriteFrame*> fontArray;
	for (int i = 1; i <= 3; i++)
	{
		sprintf(fontName, "PrepareGrowPlants%d.tiff", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(fontName);
		fontArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(fontArray, 0.8f);
	Animate* animate = Animate::create(animation);
	CallFuncN* funcn = CallFuncN::create(CC_CALLBACK_1(GameScene2::removeSprite, this));
	Sequence* seq = Sequence::create(DelayTime::create(2), animate, funcn, NULL);
	fontSprite->runAction(seq);

	for (int i = 0; i < plantsMenuArray.size(); i++) {
		log("%d", i);
		/*CCMenuItemToggle* toggle = (CCMenuItemToggle*)plantsMenuArray->objectAtIndex(i);*/
		MenuItemToggle* toggle = (MenuItemToggle*)plantsMenuArray.at(i);//将菜单中的图标设为可用
		if (toggle->getTag() == 204)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 207)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 208)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 211)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 202)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 201)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 205)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 206)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 209)
		{
			toggle->setEnabled(true);
		}
		else if (toggle->getTag() == 210)
		{
			toggle->setEnabled(true);
		}

		else if (toggle->getTag() == 203)
		{
			toggle->setEnabled(true);
		}
		else
		{

			toggle->setSelectedIndex(1);
			toggle->setEnabled(false);
		}


	}

	MoveTo* moveTo = MoveTo::create(2.0, Vec2(170, -150));
	menuSprite->runAction(moveTo);
	//地图移动
	//this->moveScenePosition();

	//添加小车
	CallFunc* funcar = CallFunc::create(CC_CALLBACK_0(GameScene2::addCar, this));
	Sequence* seqcar = Sequence::create(DelayTime::create(2), funcar, NULL);
	this->runAction(seqcar);
	//this->removeBeforeZombie();
	cherryCoolTime = 5;
	chomperCoolTime = 7;
	jalapenoCoolTime = 5;
	lilypadCoolTime = 5;
	peashooterCoolTime = 5;
	repeaterCoolTime = 5;
	squashCoolTime = 5;
	sunflowerCoolTime = 2;
	tallnutCoolTime = 5;
	threepeaterCoolTime = 5;
	wallnutCooltime = 5;
	int randomPosition = CCRANDOM_0_1() * 4;//
	timer = 0;//初始化控制僵尸数量的标志
	productMonster = 0;
	//scheduleUpdate();
	if (gamemode == 0)
		this->schedule(schedule_selector(GameScene2::setword), 4.0f);
	this->schedule(schedule_selector(GameScene2::appearZombie), 1.0f);
	this->schedule(schedule_selector(GameScene2::createSunshineWithoutSunflower), 5.0f);
	this->schedule(schedule_selector(GameScene2::checkHitWithBulletAndhero), 0.01f);
	this->schedule(schedule_selector(GameScene2::judgeCoolTime), 0.1f);
	this->schedule(schedule_selector(GameScene2::reduceCoolTime), 1.0f);
	/*this->schedule(schedule_selector(GameScene2::checkHitOtherPlantsAndZombie), 0.5f);*/
	this->schedule(schedule_selector(GameScene2::checkFial), 0.5f);
	/*   this->schedule(schedule_selector(GameScene2::checkHitCarWithZoombie), 0.01f);*/
	this->schedule(schedule_selector(GameScene2::checkHitWithHeroAndMonster), 0.1f);
	//this->schedule(schedule_selector(GameScene2::checkHitWithHeroAndZombie), 0.5f);
	/*  this->schedule(schedule_selector(GameScene2::pass), 1);*/

}

bool GameScene2::touchBegan(Touch *pTouch, Event *pEvent)
{
	log("%f, %f", pTouch->getLocation().x, pTouch->getLocation().y);
	//TMXLayer* wayLayer = _map->getLayer("plant");
	//Size _mapSize = wayLayer->getLayerSize();
	//int _height = _mapSize.height;
	//int _width = _mapSize.width;
	//for (int j = 0; j < _width; j++)
	//	for (int i = 0; i < _height; i++)
	//	{
	//	
	//		Sprite* _sp = wayLayer->getTileAt(Vec2(j, i));
	//		if (_sp)

	//	}
	return true;
}

void GameScene2::touchMoved(Touch *pTouch, Event *pEvent)
{

}

void GameScene2::touchEnded(Touch *pTouch, Event *pEvent)
{
	log("touch(%lf,%lf)", pTouch->getLocation().x, pTouch->getLocation().y);
    PlantFlag Flag = this->getFlag(pTouch->getLocation());
	if (Flag==canPlant) {
	/*	Vec2 zeroPoint = this->getPositionMessage(pTouch->getLocation());*/
		/*if (zeroPoint.x != 0 && zeroPoint.y != 0)
		{*/
			if (!plantsIsPlanted)
			{
				/*Plants* plant = (Plants*)plantsArray.at(plantsArray.size() - 1);*/
				hero* Hero_temp = (hero*)heroArray.at(heroArray.size() - 1);
				/*	if (plant->specialSkill == CollapsedSkill)
				{
				plant->setAnchorPoint(Vec2(0.5f, 0.2f));
				}
				else if (plant->specialSkill != ChimaeSkill && plant->specialSkill != BombSkill)
				{
				this->setFlagValue(pTouch->getLocation());
				}*/
				this->setFlagValue(pTouch->getLocation());//标记种植
														  /*plant->setPosition(this->getPositionMessage(pTouch->getLocation()));*/
				Hero_temp->setPosition(this->getPositionMessage(pTouch->getLocation()));
				log("Vec2(%lf,%lf)", this->getPositionMessage(pTouch->getLocation()).x, this->getPositionMessage(pTouch->getLocation()).y);
				/*	this->addChild(plant, 1);*/
				this->addChild(Hero_temp, 1);
				Hero_temp = NULL;
				plantsIsPlanted = true;
			}
		}
	/*}*/

}



void GameScene2::touchCancelled(Touch *pTouch, Event *pEvent)
{

}

void GameScene2::onExit()
{
	Layer::onExit();
	//    //plantsMenuArray->release();
	//    plantsSpriteArray->release();
	//    for(int i = 0; i < plantsArray.size(); i++)
	//    {
	//        delete plantsArray.at(i);
	//    }
	//    //plantsArray->release();
	//    //zoombieArray->release();
	//    //bulletArray->release();
	//    carArray->release();
	//    beforeZombie->release();
	//  this->unscheduleAllCallbacks();

}

Vec2 GameScene2::getPositionMessage(cocos2d::Vec2 point)
{
	//for (int i = 0; i < 9; i++)
	//{
	//	if (point.x >= (20 + i * 46) && point.x <= (20 + (i + 1) * 46))
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			if (point.y >= (15 + j * 53) && point.y <= (15 + (j + 1) * 53))
	//			{
	//				log("plants(%d,%d)", 45 + i * 46, 45 + j * 53);
	//				return Vec2((45 + i * 46), (45 + j * 53));

	//			}
	//		}
	//	}
	//}
	int x=point.x / _map->getTileSize().width;
	int y=point.y / _map->getTileSize().height;
	TMXLayer* wayLayer = _map->getLayer("plant");
	//Size _mapSize = wayLayer->getLayerSize();
	Sprite* _sp = wayLayer->getTileAt(Vec2(x,_mapSizeheigh-y-1));
	if (_sp)
	{
		_sp->setOpacity(200);
	    return Vec2((x+0.5)*_map->getTileSize().width, (y+0.5)*_map->getTileSize().height);
	}
	else
	return Vec2(0, -100);
}

void GameScene2::initFlag()
{
	//获取瓦片地图中的plant图层
	TMXLayer* wayLayer = _map->getLayer("plant");
	//得到图层的大小
	Size _mapSize = wayLayer->getLayerSize();
	int _height = _mapSize.height;
	int _width = _mapSize.width;
	for (int j = 0; j < _width; j++)
		for (int i = 0; i < _height; i++)
		{
			
			Sprite* _sp = wayLayer->getTileAt(Vec2(j, i));
			if (_sp)
			{					
				float x = _sp->getPositionX();
			    float y = _sp->getPositionY();
		     	int col = x / _map->getTileSize().width;
			    int row = y / _map->getTileSize().height;
				canPlantGrid[col][row] = canPlant;
				log("canPlantGrid[%d][%d]:%d", col, row, canPlantGrid[col][row]);
				//log("j=%d,i=%d", j, i);
				/*_sp->setOpacity(100);
				canPlantGrid[j][i] = canPlant;
				log("canPlantGrid[%d][%d]:%d", j, i, canPlantGrid[j][i]); */
			}
			else
			{
				canPlantGrid[j][_height -i-1] = cantPlant;
				
			}

		}
}
//获得相应坐标下的种植标记
PlantFlag GameScene2::getFlag(Vec2 point)
{
	//for (int i = 0; i < 9; i++)
	//{
	//	if (point.x >= (20 + i * 46) && point.x <= (20 + (i + 1) * 46))
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			if (point.y >= (15 + j * 53) && point.y <= (15 + (j + 1) * 53))
	//			{
	//				return flag[i][j];
	//			}
	//		}
	//	}
	//}
	int x=point.x/ _map->getTileSize().width;
	int y = point.y / _map->getTileSize().height;
	log("::::::(%d,%d):%d",x,y, canPlantGrid[x][y]);
	return canPlantGrid[x][y];
}
//设置相应坐标的存在植物种植的标记
void GameScene2::setFlagValue(cocos2d::Vec2 point)
{
	//for (int i = 0; i < 9; i++)
	//{
	//	if (point.x >= (20 + i * 46) && point.x <= (20 + (i + 1) * 46))
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			if (point.y >= (15 + j * 53) && point.y <= (15 + (j + 1) * 53))
	//			{
	//				flag[i][j] = 1;
	//			}
	//		}
	//	}
	//}
	int x = point.x / _map->getTileSize().width;
	int y = point.y / _map->getTileSize().height;
	canPlantGrid[x][y] = havePlant;
}
//设置将相应以种植坐标标志成可以种植的标记
void GameScene2::setFlagValue1(cocos2d::Vec2 point)
{
	//for (int i = 0; i < 9; i++)
	//{
	//	if (point.x >= (20 + i * 46) && point.x <= (20 + (i + 1) * 46))
	//	{
	//		for (int j = 0; j < 5; j++)
	//		{
	//			if (point.y >= (15 + j * 53) && point.y <= (15 + (j + 1) * 53))
	//			{
	//				flag[i][j] = 0;
	//			}
	//		}
	//	}
	//}
	int x = point.x / _map->getTileSize().width;
	int y = point.y / _map->getTileSize().height;
	canPlantGrid[x][y] = canPlant;
}
void GameScene2::addZoombie(float dt)
{
	if (productMonster <monster_number)
	{
		int random = CCRANDOM_0_1()*_monsterDatas.size();
		int randomPosition;
		switch (LEVEL)
		{
		case 1:randomPosition = 3; break;
		case 2:randomPosition = CCRANDOM_0_1() * 3 + 1; break;
		case 3:randomPosition = CCRANDOM_0_1() * 4 + 1; break;
		case 4:randomPosition = CCRANDOM_0_1() * 4 + 1; break;
		case 5:randomPosition = CCRANDOM_0_1() * 4;
			if (randomPosition >= 2)
				randomPosition += 2;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		default:break;
		}
		/*if (LEVEL == 1)
		{
			randomPosition = 3;
		}
		if (LEVEL == 2)
		{
			do {
				randomPosition = CCRANDOM_0_1() * 4;
			} while (randomPosition == 0 || randomPosition == 4);

		}
		if (LEVEL >= 3)
		{
			randomPosition = CCRANDOM_0_1() * 5;
		}*/
		monster* Monster1;
		auto monster_temp = _monsterDatas.at(random);
		Monster1 = new monster(monster_temp->getmonstertype());
		Monster1->setPosition(Vec2(580,  (randomPosition+0.5) *_map->getTileSize().height));
		monsterArray.pushBack(Monster1);
		_map->addChild(Monster1);
		Monster1->startMove();
		productMonster++;
	}

}
void GameScene2::createSunshineWithoutSunflower(float dt)
{
	Sprite* sunSprite1 = Sprite::createWithSpriteFrameName("Sun1.tiff");
	Sprite* sunSprite2 = Sprite::createWithSpriteFrameName("Sun1.tiff");
	sunSprite1->setScale(0.5f);
	sunSprite2->setScale(0.5f);
	MenuItemSprite* itemsprite = MenuItemSprite::create(sunSprite1, sunSprite2);
	Menu* menu = Menu::create(itemsprite, NULL);

	int x;
	int y;
	do {
		x = CCRANDOM_0_1() * 480;
	} while (x < 70 || x >410);
	do {
		y = CCRANDOM_0_1() * 290;
	} while (y < 70 || y >290);
	menu->setPosition(Vec2(x, 340));
	this->addChild(menu, 2);
	itemsprite->setTarget(this, menu_selector(Bullet::collectSunshine));
	//

	Vector<SpriteFrame*> sunArray;
	/*  sunArray->retain();*/
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	char name[50];
	for (int i = 1; i<23; i++)
	{
		sprintf(name, "Sun%i.tiff", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(name);
		sunArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(sunArray, 0.3f);
	Animate* animate = Animate::create(animation);
	sunSprite1->runAction(RepeatForever::create(animate));//这里不能使用菜单精灵来执行runAction动作
	MoveTo* moveTo = MoveTo::create(10, Vec2(x, y));
	menu->runAction(moveTo);
}
void GameScene2::LevelBar()
{
	Sprite* levelProgress = Sprite::create("FlagMeterLevelProgress.png");
	levelProgress->setPosition(Vec2(400, 310));
	levelProgress->setScaleY(1.1f);
	levelProgress->setScaleX(1.8f);
	this->addChild(levelProgress);
	Sprite* bar = Sprite::create("timerBar1.png");
	theLevelBar = ProgressTimer::create(bar);
	theLevelBar->setPosition(Vec2(400, 295));
	theLevelBar->setType(ProgressTimer::Type::BAR);
	this->addChild(theLevelBar);

}

void GameScene2::setLevelBar(float dt)
{
	theLevelBar->setPercentage(theLevelBarProgressBar);
	theLevelBarProgressBar++;
}

void GameScene2::appearZombie(float dt)
{
	timer++;
	if (timer <10)
	{
		if (timer == 1)
		{
			this->schedule(schedule_selector(GameScene2::addZoombie), 5);
			int count1 = monster_number * 5;
			ProgressFromTo* progressTo = ProgressFromTo::create(count1, 0, 100);
			theLevelBar->setMidpoint(Vec2(0.0f, 0.5f));
			Sequence* seq1 = Sequence::create(progressTo, NULL);
			theLevelBar->runAction(seq1);
		}
	}
	else if (timer >= 10 && timer <= 20)
	{
		if (timer == 10)
		{
			Sprite* largeWave = Sprite::create("LargeWave.png");
			largeWave->setPosition(Vec2(240, 160));
			this->addChild(largeWave);
			Blink* blink = Blink::create(3, 4);
			CallFuncN* funcn = CallFuncN::create(CC_CALLBACK_1(GameScene2::removeSprite, this));
			Sequence* seq1 = Sequence::create(blink, funcn, NULL);
			largeWave->runAction(seq1);

			CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene2::appearZombie1, this));
			Sequence* seq2 = Sequence::create(DelayTime::create(3), func, NULL);
			this->runAction(seq2);
		}
	}
	else if (timer > 20)
	{
		if (timer == 21)
		{
			Sprite* finalWave = Sprite::create("FinalWave.png");
			finalWave->setPosition(Vec2(240, 160));
			this->addChild(finalWave);
			Blink* blink = Blink::create(3, 4);
			CallFuncN* funcn = CallFuncN::create(CC_CALLBACK_1(GameScene2::removeSprite, this));
			Sequence* seq1 = Sequence::create(blink, funcn, NULL);
			finalWave->runAction(seq1);

			CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene2::appearZombie2, this));
			Sequence* seq2 = Sequence::create(DelayTime::create(3), func, NULL);
			this->runAction(seq2);
		}
		//过关条件
		if (productMonster == monster_number)
			if (monsterArray.size() <= 0)
				this->schedule(schedule_selector(GameScene2::pass), 1);
	}
}

void GameScene2::appearZombie1()
{
	this->unschedule(schedule_selector(GameScene2::addZoombie));
	this->schedule(schedule_selector(GameScene2::addZoombie), 3);
}

void GameScene2::appearZombie2()
{
	this->unschedule(schedule_selector(GameScene2::addZoombie));
	this->schedule(schedule_selector(GameScene2::addZoombie), 2);
}

void GameScene2::pass(float dt)
{
	if (zoombieArray.size() <= 0)

	{
		this->unscheduleAllCallbacks();
		CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene2::changeSuccessScene, this));
		Sequence* seq = Sequence::create(DelayTime::create(2), func, NULL);
		this->runAction(seq);
	}

}

void GameScene2::judgeCoolTime(float dt)
{
	for (int j = 0; j < plantsMenuArray.size(); j++)
	{
		MenuItemToggle* toggle = (MenuItemToggle*)plantsMenuArray.at(j);
		switch (toggle->getTag())
		{
		case CHERRY + 100:
			if (cherryCoolTime == 0 && SunNumber >= 150)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 150)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}
			break;
		case CHOMPER + 100:
			if (chomperCoolTime == 0 && SunNumber >= 150)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 150)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}
			break;
		case JALAPENO + 100:
			if (jalapenoCoolTime == 0 && SunNumber >= 125)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 125)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case LILYPAD + 100:
			if (lilypadCoolTime == 0 && SunNumber >= 25)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 25)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case PEASHOOTER + 100:
			if (peashooterCoolTime == 0 && SunNumber >= 100)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 100)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case REPEATER + 100:
			if (repeaterCoolTime == 0 && SunNumber >= 200)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 200)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case SQUASH + 100:
			if (squashCoolTime == 0 && SunNumber >= 50)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 50)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case SUNFLOWER + 100:
			if (sunflowerCoolTime == 0 && SunNumber >= 50)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 50)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case TALLNUA + 100:
			if (tallnutCoolTime == 0 && SunNumber >= 125)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 125)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case THREEPEATER + 100:
			if (threepeaterCoolTime == 0 && SunNumber >= 325)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 325)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;
		case WALLNUA + 100:
			if (wallnutCooltime == 0 && SunNumber >= 50)
			{
				toggle->setSelectedIndex(0);
				toggle->setEnabled(true);
			}
			else if (SunNumber < 50)
			{
				toggle->setEnabled(false);
				toggle->setSelectedIndex(1);
			}

			break;

		default:
			break;
		}
	}


}


void GameScene2::reduceCoolTime(float dt)
{
	for (int j = 0; j < plantsMenuArray.size(); j++)
	{
		MenuItemToggle* toggle = (MenuItemToggle*)plantsMenuArray.at(j);
		switch (toggle->getTag())
		{
		case CHERRY + 100:
			if (cherryCoolTime != 0)
			{
				cherryCoolTime--;
			}
			break;
		case CHOMPER + 100:
			if (chomperCoolTime != 0)
			{
				chomperCoolTime--;
			}
			break;
		case JALAPENO + 100:
			if (jalapenoCoolTime != 0)
			{
				jalapenoCoolTime--;

			}
			break;
		case LILYPAD + 100:
			if (lilypadCoolTime != 0)
			{
				lilypadCoolTime--;
			}
			break;
		case PEASHOOTER + 100:
			if (peashooterCoolTime != 0)
			{
				peashooterCoolTime--;
			}
			break;
		case REPEATER + 100:
			if (repeaterCoolTime != 0)
			{
				repeaterCoolTime--;
			}
			break;
		case SQUASH + 100:
			if (squashCoolTime != 0)
			{
				squashCoolTime--;
			}
			break;
		case SUNFLOWER + 100:
			if (sunflowerCoolTime != 0)
			{
				sunflowerCoolTime--;
			}
			break;
		case TALLNUA + 100:
			if (tallnutCoolTime != 0)
			{
				tallnutCoolTime--;
			}
			break;
		case THREEPEATER + 100:
			if (threepeaterCoolTime != 0)
			{
				threepeaterCoolTime--;
			}
			break;
		case WALLNUA + 100:
			if (wallnutCooltime != 0)
			{
				wallnutCooltime--;
			}
			break;
		default:
			break;
		}
	}

}
void GameScene2::changeFailedScene()
{
	TransitionCrossFade* fade = TransitionCrossFade::create(0.5, FailScene::createScene());
	Director::getInstance()->replaceScene(fade);
}

void GameScene2::checkFial(float dt)
{
	for (int i = 0; i < monsterArray.size(); i++)
	{
		if (monsterArray.size() != 0)
		{
			monster* Monster = (monster*)monsterArray.at(i);
			Vec2 MonsterPoint = _map->convertToWorldSpace(Monster->getPosition());
			if (MonsterPoint.x <= 50)//如果成立，则所有植物和僵尸停止动作
			{
				Sprite* sprite = Sprite::create("ZombiesWon.png");
				sprite->setPosition(Vec2(240, 160));
				sprite->setScale(0.5);
				/*          this->addChild(sprite);*/
				Blink* blink = Blink::create(2, 2);
				CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameScene2::changeFailedScene, this));
				Sequence* seq = Sequence::create(blink, func, NULL);
				/*               sprite->runAction(seq);*/
				monsterArray.eraseObject(Monster);
				Monster->remove();

			}
		}
	}

}
void GameScene2::changeSuccessScene()
{
	TransitionCrossFade* fade = TransitionCrossFade::create(1, PassScene::createScene());
	Director::getInstance()->replaceScene(fade);
}

void GameScene2::addCar()
{
	for (int i = 0; i < 5; i++) {
		Sprite* car = Sprite::create("LawnMower.png");
		car->setPosition(Vec2(-20, 45 + i * 53));
		this->addChild(car);
		carArray.pushBack(car);
		MoveTo* moveTo = MoveTo::create(0.5, Vec2(0, 45 + i * 53));
		car->runAction(moveTo);
	}
}
void GameScene2::removeCar(cocos2d::Node *node, cocos2d::Vector<Sprite*> array)
{
	for (int i = 0; i < array.size(); i++) {
		if (array.size() != 0)
		{
			carArray.eraseObject(array.at(i));
		}
	}
}
void GameScene2::checkHitWithHeroAndMonster(float dt)
{
	Vector<Node*> eatedhero;//存放死亡的英雄
	for (int i = 0; i < heroArray.size(); i++)//遍历英雄
	{
		hero* hero_temp = (hero*)heroArray.at(i);
		for (int j = 0; j < monsterArray.size(); j++)//遍历怪物
		{
			monster* monster_temp = (monster*)monsterArray.at(j);
			Vec2 hero_tempPoint = hero_temp->getPosition();
			Vec2 monster_tempPoint = _map->convertToWorldSpace(monster_temp->getPosition());//转换世界坐标
			if (monster_tempPoint.x - hero_tempPoint.x > 0 && monster_tempPoint.x - hero_tempPoint.x <50 && monster_tempPoint.y - hero_tempPoint.y >= 0 && monster_tempPoint.y - hero_tempPoint.y < 20)
			{
				if (!monster_temp->isAttack)
				{
					monster_temp->attack();
					monster_temp->Embattled_hero = hero_temp;
					monster_temp->isAttack = true;
					hero_temp->addmonsterAttackThishero.pushBack(monster_temp);
				}
			}
		}
		for (int k = 0; k < hero_temp->addmonsterAttackThishero.size(); k++)//遍历攻击这个英雄的怪物数组
		{
			if (((monster*)hero_temp->addmonsterAttackThishero.at(k))->tempattack_frequency++>((monster*)hero_temp->addmonsterAttackThishero.at(k))->attack_frequency)//定时器时间*（attack_frequency-tempattack_frequency）=造成伤害间隔
			{
				hero_temp->blood = hero_temp->blood - ((monster*)hero_temp->addmonsterAttackThishero.at(k))->damage;
				((monster*)hero_temp->addmonsterAttackThishero.at(k))->tempattack_frequency = 0;
				char ch[10];
				sprintf(ch, "%d!", ((monster*)hero_temp->addmonsterAttackThishero.at(k))->damage);
				Label *bleed = Label::createWithSystemFont(ch, "Verdana-Bold", 15);
				bleed->setPosition(hero_temp->getPosition().x, hero_temp->getPosition().y + 20);
				bleed->setScale(1.0f);
				bleed->setColor(Color3B::RED);
				this->addChild(bleed);
				CallFuncN* funcn = CallFuncN::create(CC_CALLBACK_1(GameScene2::removeSprite, this));
				MoveBy* moveBy = MoveBy::create(0.5f, Vec2(0, 20));
				Sequence* seq3 = Sequence::create(moveBy, funcn, NULL);
				bleed->runAction(seq3);
			}
			if (hero_temp->blood <= 0)
			{
				for (int i = 0; i < hero_temp->addmonsterAttackThishero.size(); i++)
				{
					monster* romvemonster = (monster*)hero_temp->addmonsterAttackThishero.at(i);//取出攻击英雄的怪物
					romvemonster->tempattack_frequency = 0;
					romvemonster->startMove();//怪物重新开始移动
					romvemonster->isAttack = false;
				}
				eatedhero.pushBack(hero_temp);
				setFlagValue1(hero_temp->getPosition());//清除以种植标志
				hero_temp->removeFromParent();//移除英雄将其释放
				break;
			}

		}
	}
	for (int i = 0; i < eatedhero.size(); i++)
	{
		if (eatedhero.size() != 0)
		{
			heroArray.eraseObject(eatedhero.at(i));
			((hero*)eatedhero.at(i))->remove();
		}
	}
}
void GameScene2::createHeroShoote(float dt)
{

	for (int i = 0; i < heroArray.size(); i++)
	{
		hero* hero_temp = (hero*)heroArray.at(i);
		for (int j = 0; j < monsterArray.size(); j++)//检测当没有僵尸的时候植物不发射子弹
		{
			monster* mSprite = (monster*)monsterArray.at(j);
			Point hPosition = hero_temp->getPosition();
			Point zPosition = _map->convertToWorldSpace(mSprite->getPosition());//转换世界坐标
			if (zPosition.x - hPosition.x < hero_temp->Attack_range && abs(zPosition.y - hPosition.y) <20 && zPosition.x<450)
				if (hero_temp->isshoot)
				{

					hero_temp->createPeaInterval--;
					Bullet* bullet;
					if (hero_temp->createPeaInterval == 0)
					{
						bullet = new Bullet(hero_temp, hero_temp->getPosition(), this);
						hero_temp->createPeaInterval = hero_temp->tempCreatePeaInterval;
					}
					/*	if (zoombie->blood <= 0)
					{
					hero_temp->startMove();
					}*/
				}
		}
	}


}
void GameScene2::checkHitWithBulletAndhero(float dt)
{
	Vector<Sprite*> tempBulletArray;
	Vector<Sprite*> unHitBullet;
	Bullet* bullet;
	monster* monster_temp;
	for (int i = 0; i < bulletArray.size(); i++)
	{
		bullet = (Bullet*)bulletArray.at(i);
		for (int j = 0; j < monsterArray.size(); j++)
		{

			monster_temp = (monster*)monsterArray.at(j);
			Vec2 bulletPoint = bullet->getPosition();
			Vec2 monsterPoint = _map->convertToWorldSpace(monster_temp->getPosition());//因为僵尸是加在pSprite背景层上的，所以必须把pSprite转换为世界坐标，这样僵尸坐标才能正确显示;
			if (monsterPoint.x - bulletPoint.x>-20 && monsterPoint.x - bulletPoint.x<10 && bulletPoint.y - monsterPoint.y>-30 && bulletPoint.y - monsterPoint.y<40)
			{
				tempBulletArray.pushBack(bullet);
				char ch[10];
				sprintf(ch, "%d!", bullet->damage);
				Label *bleed = Label::createWithSystemFont(ch, "Verdana-Bold", 15);
				bleed->setPosition(monsterPoint.x, monsterPoint.y + 20);
				bleed->setScale(1.0f);
				bleed->setColor(Color3B::RED);
				this->addChild(bleed);
				CallFuncN* funcn = CallFuncN::create(CC_CALLBACK_1(GameScene2::removeSprite, this));
				MoveBy* moveBy = MoveBy::create(0.5f, Vec2(0, 20));
				Sequence* seq3 = Sequence::create(moveBy, funcn, NULL);
				bleed->runAction(seq3);
				monster_temp->blood -= bullet->damage;
				bullet->removeFromParent();
				if (monster_temp->blood <= 0)
				{
					if (monster_temp->isAttack)
						((hero*)monster_temp->Embattled_hero)->addmonsterAttackThishero.eraseObject(monster_temp);//如果怪物的状态是攻击则删除攻击的英雄中的相应怪兽
					monsterArray.eraseObject(monster_temp);//移除怪物
					monster_temp->remove();
					break;
				}

			}
			else if (bullet->getPosition().x == 500)
			{
				bullet = (Bullet*)bulletArray.at(i);
				unHitBullet.pushBack(bullet);
				bullet->removeFromParent();
			}

		}
	}


	for (int i = 0; i < tempBulletArray.size(); i++) {
		bulletArray.eraseObject(tempBulletArray.at(i));
	}
	for (int i = 0; i <unHitBullet.size(); i++) {
		bulletArray.eraseObject(unHitBullet.at(i));
	}
}
GameScene2::~GameScene2()
{
	/*for (int i = 0; i<_map->getMapSize().height; i++)
	{
		delete[(int)_map->getMapSize().width]canPlantGrid[i];
		canPlantGrid[i] = NULL;
	}
	delete[(int)_map->getMapSize().height] canPlantGrid;
	canPlantGrid = NULL;*/
}
