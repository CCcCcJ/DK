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

	// ����һ����Ա�����Լ�get##funName������û��set������get##funName����ֻ����������û�ж��塣��������:
	//��̬��������������GameMapʵ��
	static GameMap* gameMapWithTMXFile(const std::string&  tmxFile);

	
protected:

};
#endif
