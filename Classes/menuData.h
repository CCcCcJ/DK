#ifndef MENUDATA_H_
#define MENUDATA_H_
#include"cocos2d.h"
#include"string.h"
USING_NS_CC;

class MenuData :public Ref
{
private:
	bool availability;
	int tag;
	std::string name1;
	std::string name2;
public:
	static MenuData* create();
	std::string getmember_name1();
	std::string getmenber_name2();
	void  setmenu_member(int number);
	bool getavailability();
	int gettag();


};
#endif // !MENUDATA_H_
