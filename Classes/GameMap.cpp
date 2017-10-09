#include"cocos2d.h"
#include"GameMap.h"
using namespace cocos2d;

GameMap::~GameMap(void)
{
	this->unscheduleAllSelectors();
}
//静态方法，用于生成GameMap实例
GameMap* GameMap::gameMapWithTMXFile(const std::string&  tmxFile)
{
	//new一个对象
	GameMap *pRet = new GameMap();
	//调用init方法
	if (pRet->initWithTMXFile(tmxFile))
	{
		//将实例放入autorelease池，统一由引擎控制对象的生命周期
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}