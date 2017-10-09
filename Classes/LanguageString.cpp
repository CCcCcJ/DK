#include "LanguageString.h"

LanguageString* LanguageString::instance;
//Dictionary * LanguageString::strings;


LanguageString * LanguageString::getInstance()
{
	if(instance == NULL)
	{
		instance = new LanguageString();
	}
	
	return instance;
}

__String* LanguageString::getLanguageString(const char* strName)
{
	//LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();

	////if(strings == NULL)
	//if (plist_map.empty())
	//{
	//	switch (currentLanguageType)
	//	{
	//		case kLanguageEnglish:
	//		{
	//			//strings = Dictionary::createWithContentsOfFile("string_en.plist");
	//			//strings->retain();
	//			 plist_map = FileUtils::getInstance()->getValueMapFromFile("string_en.plist");
	//			break;
	//		}

	//		case kLanguageChinese:
	//		{
	//			//strings = Dictionary::createWithContentsOfFile("string_zh.plist");
	//			//strings->retain();
	//			plist_map = FileUtils::getInstance()->getValueMapFromFile("string_zh.plist");
	//			break;
	//		}
	//	}
	//}
	//String* retStr = static_cast<String*>(strings->objectForKey(strName));
	//return retStr;
	//从plist文件中根据键值来得到字符串
	plist_map = FileUtils::getInstance()->getValueMapFromFile("string_zh.plist");
	str = plist_map.at(strName).asString();
	return String::create(str);
}