#include"readleveldata.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
 rapidjson::Document readleveldata::document;
readleveldata* readleveldata::create(int level)
{
	readleveldata *sprite = new readleveldata();

	if (sprite)
	{
		std::string filePath = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("%d.data", level));
		std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
		document.Parse<0>(contentStr.c_str());
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
int readleveldata::getmonster_number()
{
	//����ÿ�����޳��ֵ�����
	monster_number = document["number"].GetInt();
	return monster_number;
}
Vector<MenuData*> readleveldata::get_menuDatas()
{
	//����һ���п�ѡ����ս����Ӣ�ۣ�������Vector������
	const rapidjson::Value& menu_Array = document["menu"];
	for (unsigned int i = 0; i < menu_Array.Size(); i++)
	{
		int menutag = menu_Array[i]["menutag"].GetInt();
		auto menuData = MenuData::create();
		//��ȡ�ļ��еĲ˵���tag
		menuData->setmenu_member(menutag);
		_menuDatas.pushBack(menuData);
	}
	return  _menuDatas;
}
Vector<MonsterData*> readleveldata::get_monsterDatas()
{

	
	const rapidjson::Value& monster_Array = document["monsters"];
	//����һ���г��ֵĹ�������ಢ����Vector������
	for (unsigned int i = 0; i < monster_Array.Size(); i++)
	{
		std::string name = monster_Array[i]["name"].GetString();
		auto monsterData = MonsterData::create();
		monsterData->setmonstertype(name);
		_monsterDatas.pushBack(monsterData);
	}
	return _monsterDatas;
}
std::string readleveldata::get_background()
{
	
	//��ñ���ͼ������
	BackGround = document["background"].GetString();
	return BackGround;
}