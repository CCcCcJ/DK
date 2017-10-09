#ifndef __LANGUAGESTRING__H__
#define __LANGUAGESTRING__H__

#include "cocos2d.h"
USING_NS_CC;
class LanguageString
{
private:
	static LanguageString* instance;
	//static Dictionary *strings;
	ValueMap plist_map;
	std::string str;
public:
	static LanguageString * getInstance();
    __String* getLanguageString(const char* strName);

};

#endif