#include"cocos2d.h"
#include"GameMap.h"
using namespace cocos2d;

GameMap::~GameMap(void)
{
	this->unscheduleAllSelectors();
}
//��̬��������������GameMapʵ��
GameMap* GameMap::gameMapWithTMXFile(const std::string&  tmxFile)
{
	//newһ������
	GameMap *pRet = new GameMap();
	//����init����
	if (pRet->initWithTMXFile(tmxFile))
	{
		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}