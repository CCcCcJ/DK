#ifndef LOADSKELETONDATA_H_
#define LOADSKELETONDATA_H_
#include "cocos2d.h"
#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
using namespace spine;
USING_NS_CC;
class loadskeletondata
{
    public :
	static  void loadFrame();
	static loadskeletondata* instance;
	static loadskeletondata * getInstance();
	static spSkeletonData* hero_skeletonData0;
	static spAnimationStateData* hero_stateData0;
	static spSkeletonData* hero_skeletonData1;
	static spAnimationStateData* hero_stateData1;
	static spSkeletonData* hero_skeletonData2;
	static spAnimationStateData* hero_stateData2;
	static spSkeletonData* hero_skeletonData3;
	static spAnimationStateData* hero_stateData3;
	static spSkeletonData* hero_skeletonData4;
	static spAnimationStateData* hero_stateData4;
	static spSkeletonData* hero_skeletonData5;
	static spAnimationStateData* hero_stateData5;
	static spSkeletonData* hero_skeletonData6;
	static spAnimationStateData* hero_stateData6;
	static spSkeletonData* hero_skeletonData7;
	static spAnimationStateData* hero_stateData7;
	static spSkeletonData* hero_skeletonData8;
	static spAnimationStateData* hero_stateData8;
	static spSkeletonData* hero_skeletonData9;
	static spAnimationStateData* hero_stateData9;
	static spSkeletonData* hero_skeletonData10;
	static spAnimationStateData* hero_stateData10;
	//static spSkeletonData* hero_skeletonData3;
	//static spAnimationStateData* hero_stateData3;
	static spSkeletonData* monster_skeletonData0;
	static spAnimationStateData* monster_stateData0;
	static spSkeletonData* monster_skeletonData1;
	static spAnimationStateData* monster_stateData1;
	static spSkeletonData* monster_skeletonData2;
	static spAnimationStateData* monster_stateData2;
	static spSkeletonData* monster_skeletonData3;
	static spAnimationStateData* monster_stateData3;
	static spSkeletonData* monster_skeletonData4;
	static spAnimationStateData* monster_stateData4;
	 ~loadskeletondata();
};
#endif // !LOADSKELETONDATA_H_

