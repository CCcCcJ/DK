#include"monsterData.h"
void  MonsterData::setmonstertype(std::string name)
{
	if (name == "monster1")
		monstertype = monster1;
	else if (name == "monster2")
		monstertype = monster2;
	else if (name == "monster3")
		monstertype = monster3;
	else if (name == "monster4")
		monstertype = monster4;
	else if (name == "monster5")
		monstertype = monster5;
	else if (name == "monster6")
		monstertype = monster6;
	else if (name == "monster7")
		monstertype = monster7;
	else if (name == "monster8")
		monstertype = monster8;
	else if (name == "monster9")
		monstertype = monster9;
	else if (name == "monster10")
		monstertype = monster10;

}
MonsterType MonsterData::getmonstertype()
{
	return monstertype;
}
 MonsterData* MonsterData::create()
{
	MonsterData *sprite = new MonsterData();
	if (sprite)
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}