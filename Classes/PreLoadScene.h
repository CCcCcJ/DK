#ifndef PRELOADSCENE_H_
#define PRELOADSCENE_H_
#include "cocos2d.h"
USING_NS_CC;	
namespace androidsql
{
	bool isFileExist(const char* pFileName);
	void copyData(const char * pFileName);
}
class PreLoad :public cocos2d::Layer
{
public:
	static Scene* createScene(int x,int selectLevel);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	void loadMusic();
	static char **result;
	static int type;//1重新开始0继续
	void progressupdate(float dt);
	bool finshflag;
	CREATE_FUNC(PreLoad);

};
#endif