//
//  GameScene.h
//  PlantsVSZombies
//
//  Created by HeZhiTao on 13-11-12.
//
//

#ifndef __PlantsVSZombies__GameScene__
#define __PlantsVSZombies__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "monster.h"
#include"monsterData.h"
#include "ui/CocosGUI.h"
#include"menuData.h"
USING_NS_CC;
using namespace ui;
USING_NS_CC_EXT;
//using namespace cocos2d::extension;
#define CHERRY 101//A英雄
#define CHOMPER 102//B英雄
#define JALAPENO 103//C英雄
#define LILYPAD 104//D英雄
#define PEASHOOTER 105//O英雄
#define REPEATER 106//U英雄
#define SQUASH 107//I英雄
#define SUNFLOWER 108//向日葵
#define TALLNUA 109//高坚果
#define THREEPEATER 110//豌豆射手3
#define WALLNUA 111//坚果
#define MAXLEVEL 5
typedef enum
{
	//可以种植
	canPlant = 0,
	//已经种植
	havePlant,
	//禁止种植
	cantPlant,

}PlantFlag;
class GameScene2 : public cocos2d::Layer
{
public:
	virtual void onEnter();
    virtual bool init();
	virtual ~GameScene2();
    static cocos2d::Scene* createScene(int selectLevel,int type);
    CREATE_FUNC(GameScene2);
	void menuItemToggle(Ref* pSender);
    void moveScenePosition();
    void sunAction();
    void plantsMenu(Ref* tag);
	MenuItemToggle* createMenuItem(const char* plantName,const char* plantName2, int tag);
    MenuItemToggle* createMenuItem1(const char* plantName,const char* plantName2, int tag);
    void resetBarMenu();
    void beSure();//菜单确认按钮
    void addMenu();//添加菜单
    void plantingPlant(Ref* plant);//种植植物
    Vec2 getPositionMessage(Vec2 point);
    void initFlag();//
	PlantFlag getFlag(Vec2 point);
    void setFlagValue(Vec2 point);//设置植物种植位置的标志
     void setFlagValue1(Vec2 point);
  //  void createSunshine(float dt);//创建阳光
    //void createShoote(float df);//创建子弹
	void createHeroShoote(float df);//英雄子弹
    void removeSprite(Node* sprite);
    void addZoombie(float dt);
  //  void checkHitWithBulletAndPlant(float dt);//检测子弹与僵尸的碰撞
	void checkHitWithHeroAndMonster(float dt);//检测英雄与怪兽的碰撞
    void setSunNumberLB(float dt);
    void createSunshineWithoutSunflower(float dt);//非向日葵产生的阳光
    void LevelBar();//初始化关卡进度条
    void setLevelBar(float dt);//设置关卡进度条
    void appearZombie(float dt);//根据timer控制僵尸出现的数量
    void appearZombie1();
    void appearZombie2();
    void pass(float dt);//过关
    void judgeCoolTime(float dt);//判断植物的冷却时间
    void reduceCoolTime(float dt);//每秒钟减少一次冷却时间
    //void checkHitOtherPlantsAndZombie(float dt);//检测其他植物（辣椒，食人花等），与僵尸的碰撞
    //void zoombieBoomDie(Ref* zoombie);//僵尸被炸死的动作
    //void collapseZombie(Ref* zoombie);//僵尸被南瓜压死的动作
    //void chomperAction1(Ref* plant);//食人花正常动作
    //void chomperAction2(Ref* plant);//食人花吃僵尸的动作
    //void chomperAction3(Ref* plant);//食人花咀嚼僵尸的动作
    void changeFailedScene();//切换到失败场景
    void checkFial(float dt);//检测僵尸是否进入房子
    void changeSuccessScene();
    void addCar();//添加小车
//    void checkHitCarWithZoombie(float dt);
    void removeCar(Node* node, Vector<Sprite*> array);
    //void initBeforeZombie();//初始化刚开始出现的僵尸，游戏开始后移除
    //void removeBeforeZombie();
	void checkHitWithBulletAndhero(float dt);
	void setword(float dt);
	void Judge(Ref* pSender);
	void readword(Ref* pSender);//读单词
	void menuPauseCallback(cocos2d::Ref* pSender);
    virtual void onExit();
    virtual bool touchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void touchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void touchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void touchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
public:

    //Sprite* pSprite;//背景精灵
	PlantFlag **canPlantGrid;
    Sprite* menuSprite;//菜单
	MenuItemLabel* wordLabel;//单词选项
	char answer[20];
	int answer_tag;
	//MenuItemLabel* ChineseLabel;
	Menu* chinesemenu;//储存中文选项的标签菜单
	Menu* wordmenu;//存储单词标签菜单
    Sprite* barMenuSprite;//菜单条
    //int theZombieArray[20];
	int monster_number;//每一关怪兽的数量
	Vector<MonsterData*> _monsterDatas;//存放读取出来的每个怪兽的数据
	Vector<MenuData*>_menuDatas;//存放读取出来的每个菜单成员的数据
    Vector<MenuItem*> plantsMenuArray;//菜单中存放的数组
	Vector<MenuItem*> Menutemp_Array1;//记录菜单中第一列图标
	Vector<MenuItem*> Menutemp_Array2;//记录菜单中第二列图标
    Vector<Sprite*> plantsArray;//游戏中存放的植物
	Vector<Sprite*> plantsSpriteArray;//存放选择植物是生成的临时植物精灵
	Vector<Sprite*> zoombieArray;//存放游戏中的僵尸
	Vector<Node*> monsterArray;//存放游戏中的怪物
	Vector<Node*> heroArray;//存放游戏中的英雄
	Vector<Sprite*> carArray;
    Label* sunNumberLB;
	Label* wordLB;//英文的标签
	//char **result;//存数据库的数组
	Label* ChineseLB_A;//中文的标签
	Label* ChineseLB_B;//中文的标签
	Label* ChineseLB_C;//中文的标签
	Vector<Sprite*>  beforeZombie;
    bool plantsIsPlanted;//植物是否被种植的标志
    int flag[9][5];//不能重复种植的标志,0可以种植，1不可以种植
    char sunNum[10];
    int timer;//时间标志，控制僵尸出现的数量
    //ControlSlider* theLevelBar;//关卡进度条
	ProgressTimer* theLevelBar;
    int theLevelBarProgressBar;//设置进度条的值
    int thePassNumberOfZombie;//过关所需要打死僵尸的数量
    int productMonster;//每关要产生僵尸的数量
	Label* _goldLabel;//金币数
	Label* labelScore;//分数
    //CCMenuIteToggle中每个菜单项的冷却时间
	TMXTiledMap* _map;//瓦片地图
	int _mapSizeheigh;
	int _mapSizewidth;
    int cherryCoolTime;
    int chomperCoolTime;
    int jalapenoCoolTime;
    int lilypadCoolTime;
    int peashooterCoolTime;
    int repeaterCoolTime;
    int squashCoolTime;
    int sunflowerCoolTime;
    int tallnutCoolTime;
    int threepeaterCoolTime;
    int wallnutCooltime;
    static  int SunNumber;  //初始化太阳的个数
    static int LEVEL;
    static int SCORE;
    static int GOLD;
	static int gamemode;
	static double originlength;
	static Vector<Sprite*> bulletArray;
};


#endif /* defined(__PlantsVSZombies__GameScene__) */
