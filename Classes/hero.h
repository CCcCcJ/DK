#ifndef HERO_H_
#define HERO_H_
#include "cocos2d.h"
#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
#include "monster.h"
using namespace spine;
USING_NS_CC;
typedef enum
{
	hero1 = 0,
	hero2,
	hero3,
	hero4,
	hero5,
	hero6,
	hero7,
	hero8,
	hero9,
	hero10,
	hero11,
	hero12,
	hero13,
	hero14,
	hero15,
	hero16,
}HeroType;
class hero :public Node
{
public:
	void remove();
	hero(HeroType herotype);
	double Attack_range;//攻击范围
	bool isshoot;
	int createPeaInterval=5;
	int tempCreatePeaInterval=5;
	int blood;
	HeroType type;
	~hero();
	void startMove();
	Vector<Node*> addmonsterAttackThishero;
	void runheroAction(char* action_name);



	//spAtlas* _atlas;
	//spAttachmentLoader* _attachmentLoader;
	//spSkeletonData* _skeletonData0;
	//spAnimationStateData* _stateData0;
	//spSkeletonData* _skeletonData1;
	//spAnimationStateData* _stateData1;
	//spSkeletonData* _skeletonData2;
	//spAnimationStateData* _stateData2;
	SkeletonAnimation * skeletonNode;
};

#endif