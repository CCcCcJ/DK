#ifndef GAMEMAP_H_
#define GAMEMAP_H_
#include"cocos2d.h"
using namespace cocos2d;
class GameMap : public cocos2d::TMXTiledMap
{
public:
	GameMap(void);
	~GameMap(void);
	TMXLayer* plant;

	// 声明一个成员变量以及get##funName函数，没有set函数。get##funName函数只有声明，而没有定义。代码如下:
	//静态方法，用于生成GameMap实例
	static GameMap* gameMapWithTMXFile(const std::string&  tmxFile);

	
protected:

};
#endif
