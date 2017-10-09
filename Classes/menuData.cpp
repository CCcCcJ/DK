#include"menuData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
MenuData* MenuData::create()
{
	MenuData *sprite = new MenuData();
	if (sprite)
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void  MenuData::setmenu_member(int number)
{
	tag = number;
	switch (number)
	{
	case 101:name1 = "rolecard/heroa.png"; name2 = "rolecard/heroaNOT.png"; break;
	case 102:name1 = "rolecard/herob.png"; name2 = "rolecard/herobNOT.png"; break;
	case 103:name1 = "rolecard/heroc.png"; name2 = "rolecard/herocNOT.png"; break;
	case 104:name1 = "rolecard/herod.png"; name2 = "rolecard/herodNOT.png"; break;
	case 105:name1 = "rolecard/heroo.png"; name2 = "rolecard/herooNOT.png"; break;
	case 106:name1 = "rolecard/herou.png"; name2 = "rolecard/herouNOT.png"; break;
	case 107:name1 = "rolecard/heroi.png"; name2 = "rolecard/heroiNOT.png"; break;
	case 108:name1 = "rolecard/herou.png"; name2 = "rolecard/herouNOT.png"; break;
	case 109:name1 = "rolecard/herou.png"; name2 = "rolecard/herouNOT.png"; break;
	case 110:name1 = "rolecard/herou.png"; name2 = "rolecard/herouNOT.png"; break;
	case 111:name1 = "rolecard/herou.png"; name2 = "rolecard/herouNOT.png"; break;
	default:break;
	}
	availability = UserDefault::getInstance()->getBoolForKey(name1.c_str(),false);

}
bool MenuData::getavailability()
{
	return availability;
}
int MenuData::gettag()
{
	return tag;
}
std::string MenuData::getmember_name1()
{
	return name1;
}
std::string MenuData::getmenber_name2()
{
	return name2;
}
