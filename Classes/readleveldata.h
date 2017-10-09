#ifndef  READLEVELDATA_H_
#define  READLEVELDATA_H_
#include "menuData.h"
#include"cocos2d.h"
#include"monsterData.h"
#include<iostream>
#include "cocos-ext.h"
USING_NS_CC_EXT;
using namespace cocos2d;
class readleveldata :public Ref
{
private:
	Vector<MenuData*>  _menuDatas;//存放读取出来的每个菜单成员的数据
	Vector<MonsterData*>  _monsterDatas;//存放读取出来的每个怪兽的数据
	int  monster_number;//每一关怪兽的数量
	std::string  BackGround;//背景图片名称
public:
	static rapidjson::Document document;
	static readleveldata* create(int level);
	int getmonster_number();
	 Vector<MenuData*> get_menuDatas();
	 Vector<MonsterData*> get_monsterDatas();
	 std::string get_background();


};
#endif // ! MONSTERDATA_H_