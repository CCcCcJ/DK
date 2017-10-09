#include"hero.h"
#include"Loadskeletondata.h"
hero::hero(HeroType herotype)
{

	type = herotype;
	switch (herotype)
	{	
		//英雄a
	    case hero1:
			blood = 50;
			Attack_range = 200;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData0, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData0);
			skeletonNode->setAnimation(0, "walk", true);
			skeletonNode->setPosition(20, 0);
			this->addChild(skeletonNode); 
			break;
		//英雄b
		case hero2:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData1, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData1);
			skeletonNode->setAnimation(0, "walk", true);
			skeletonNode->setPosition(0, 0);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
		//英雄c
		case hero3:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData3, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData3);
			skeletonNode->setAnimation(0, "walk", true);
			skeletonNode->setPosition(-30, 20);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
			//英雄p
		case hero4:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData6, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData6);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(-5, 10);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
			//英雄o
		case hero5:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData10, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData10);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(-10, 15);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
			//英雄u
		case hero6:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData8, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData8);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(0, 20);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
			//英雄i
		case hero7:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData2, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData2);
			skeletonNode->setAnimation(0, "walk", true);
			skeletonNode->setPosition(-10, 0);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
			//英雄m
		case hero8:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData7, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData7);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(10, -15);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;

			//英雄n
		case hero9:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData5, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData5);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(0, -15);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;

			//英雄f
		case hero10:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData9, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData9);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(-10, 0);
			skeletonNode->setScale(2);
			this->addChild(skeletonNode);
			break;
			//英雄g
		case hero11:
			blood = 60;
			Attack_range = 150;
			isshoot = true;
			skeletonNode = SkeletonAnimation::createWithData(loadskeletondata::getInstance()->hero_skeletonData4, false);
			skeletonNode->setAnimationStateData(loadskeletondata::getInstance()->hero_stateData4);
			skeletonNode->setAnimation(0, "attack", true);
			skeletonNode->setPosition(-20, -15);
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

void hero::startMove()
{
	//要根据距离计算出时间（让速度是一个恒定的值）
	float x = this->getPosition().x;
	float y = this->getPosition().y;
	float distance = (x + 70+580);
	float time = distance*0.03;
	MoveTo* move = MoveTo::create(time, Vec2(580, this->getPosition().y));
	//CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(Zoombie::remove));
	Sequence* seq = Sequence::create(move, NULL);
	this->runAction(seq);
}
void hero::runheroAction(char* action_name)
{
	this->skeletonNode->setAnimation(0, action_name, true);
}
hero::~hero()
{

}
void hero::remove()
{
	this->removeFromParentAndCleanup(true);
	this->removeFromParent();
}