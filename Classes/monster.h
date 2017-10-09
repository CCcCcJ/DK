#ifndef MONSTER_H_
#define MONSTER_H_
#include "cocos2d.h"
#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
#include"hero.h"
using namespace spine;
USING_NS_CC;
typedef enum
{
	monster1 = 0,
	monster2,
	monster3,
	monster4,
	monster5,
	monster6,
	monster7,
	monster8,
	monster9,
	monster10,

}MonsterType;
class monster:public Node
{
public:
	int blood;
	MonsterType type;	
	bool isAttack;
	monster(MonsterType monsterType);
	//void loadFrameFiles();
	Node* Embattled_hero;
	void remove();
	int attack_frequency;
	int tempattack_frequency;
	int damage;
	Vector<Sprite*> addheroAttackThismonster;//存放攻击这个植物的僵尸
	~monster();
	void startMove();
	void attack();
	void runmonsterAction(char* action_name);
protected:
	
	//spAtlas* _atlas;
	//spAttachmentLoader* _attachmentLoader;
	//spSkeletonData* _skeletonData;
	//spAnimationStateData* _stateData;

	SkeletonAnimation *skeletonNode;
};

#endif