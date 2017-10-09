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
	Vector<MenuData*>  _menuDatas;//��Ŷ�ȡ������ÿ���˵���Ա������
	Vector<MonsterData*>  _monsterDatas;//��Ŷ�ȡ������ÿ�����޵�����
	int  monster_number;//ÿһ�ع��޵�����
	std::string  BackGround;//����ͼƬ����
public:
	static rapidjson::Document document;
	static readleveldata* create(int level);
	int getmonster_number();
	 Vector<MenuData*> get_menuDatas();
	 Vector<MonsterData*> get_monsterDatas();
	 std::string get_background();


};
#endif // ! MONSTERDATA_H_