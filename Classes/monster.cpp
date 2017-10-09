#include "monster.h"
#include"Loadskeletondata.h"
monster::monster(MonsterType monsterType)
{
	type = monsterType;
	isAttack = false;
	switch (monsterType)
	{
		//怪物“1”
	case monster1:
		attack_frequency = 10;
		tempattack_frequency = 0;
		damage = 20;
		blood = 80;
		skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->monster_skeletonData0, false);
		skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->monster_stateData0);
		skeletonNode->setAnimation(0, "walk", true);
		skeletonNode->setPosition(0, 0);
		skeletonNode->setScale(2);
		this->addChild(skeletonNode);
		break;
		//怪物”5“
	case monster2:
		damage = 30;
		attack_frequency = 10;
		tempattack_frequency = 0;
		blood = 80;
		skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->monster_skeletonData1, false);
		skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->monster_stateData1);
		skeletonNode->setAnimation(0, "walk", true);
		//skeletonNode->addAnimation(0, "jump", false, 3);
		//skeletonNode->addAnimation(0, "run", true);
		skeletonNode->setPosition(0, 0);
		skeletonNode->setScale(2);
		this->addChild(skeletonNode);
		break;
		//怪物“3”
	case monster3:
		damage = 30;
		attack_frequency = 10;
		tempattack_frequency = 0;
		blood = 80;
		skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->monster_skeletonData2, false);
		skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->monster_stateData2);
		skeletonNode->setAnimation(0, "walk", true);
		skeletonNode->setPosition(0, 0);
		skeletonNode->setScale(2);
		this->addChild(skeletonNode);
		break;
		//怪物“2”
	case monster4:
		damage = 30;
		attack_frequency = 10;
		tempattack_frequency = 0;
		blood = 80;
		skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->monster_skeletonData3, false);
		skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->monster_stateData3);
		skeletonNode->setAnimation(0, "walk", true);
		skeletonNode->setPosition(0, -20);
		skeletonNode->setScale(2);
		this->addChild(skeletonNode);
		break;
		//怪物“6”
	case monster5:
		damage = 30;
		attack_frequency = 10;
		tempattack_frequency = 0;
		blood = 80;
		skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->monster_skeletonData4, false);
		skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->monster_stateData4);
		skeletonNode->setAnimation(0, "walk", true);
		skeletonNode->setPosition(0, 0);
		skeletonNode->setScale(2);
		this->addChild(skeletonNode);
		break;
	default:break;


	}
	
	/*	auto skeletonNode = SkeletonAnimation::createWithFile("dragon.json", "dragon.atlas");

		skeletonNode->setAnimation(0, "flying", true);
		skeletonNode->getSkeleton()->flipX = 1;
		skeletonNode->setScale(0.1);
		skeletonNode->setTimeScale(0.6f);
		this->addChild(skeletonNode);*/
	
	/*	 skeletonNode->createWithFile("spineboy.json", "spineboy.atlas");
		skeletonNode->setAnimation(0, "flying", true);
		skeletonNode->getSkeleton()->flipX = 1;
		skeletonNode->setScale(0.1);
		skeletonNode->setTimeScale(0.6f);
		this->addChild(skeletonNode);*/


	


}

void monster::startMove()
{
	//要根据距离计算出时间（让速度是一个恒定的值）
	this->stopAllActions();
	switch (type)
	{
	case monster1:skeletonNode->setAnimation(0, "walk", true); break;
	case monster2:skeletonNode->setAnimation(0, "walk", true); break;
	case monster3:skeletonNode->setAnimation(0, "walk", true); break;
	case monster4:skeletonNode->setAnimation(0, "walk", true); break;
	case monster5:skeletonNode->setAnimation(0, "walk", true); break;
	default:break;
	}
	float x = this->getPosition().x;
	float y = this->getPosition().y;
	float distance = (x + 70);
	float time = distance*0.03;
	MoveTo* move = MoveTo::create(time, Vec2(-70, this->getPosition().y));
	//CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(Zoombie::remove));
	Sequence* seq = Sequence::create(move ,NULL);
	this->runAction(seq);
}
void monster::attack()
{
	this->stopAllActions();
	switch (type)
	{
	    case monster1:skeletonNode->setAnimation(0, "attack", true); break;
		case monster2:skeletonNode->setAnimation(0, "attack", true); break;
		case monster3:skeletonNode->setAnimation(0, "attack", true); break;
		case monster4:skeletonNode->setAnimation(0, "attack", true); break;
		case monster5:skeletonNode->setAnimation(0, "attack", true); break;
		default:break;
	}

}
void monster::runmonsterAction(char* action_name)
{
	this->skeletonNode->setAnimation(0, action_name, true);
}
void monster::remove()
{
	this->removeFromParentAndCleanup(true);
	this->removeFromParent();
}
monster::~monster()
{
	//delete Embattled_hero;
	//spSkeletonData_dispose(_skeletonData);
	//spAnimationStateData_dispose(_stateData);
	//spAttachmentLoader_dispose(_attachmentLoader);
	//spAtlas_dispose(_atlas);
}
