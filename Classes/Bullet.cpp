//
//  Bullet.cpp
//  PlantsVSZombies
//
//  Created by user on 13-6-5.
//
//

#include "Bullet.h"
#include "MenuScene.h"
#include "GameScene2.h"
Bullet::~Bullet()
{
 
}

void Bullet::moveSunshine(Node *sender)
{

    GameScene2::SunNumber = GameScene2::SunNumber + 50;
	sender->removeFromParent();
}
//void Bullet::moveSunshine(Node *sender, Menu *m)
//{
//	extern int SunNumber;
//	SunNumber = SunNumber + 50;
//	m->removeFromParent();
//}
void Bullet::collectSunshine(Ref *object)
{
	auto sender = (Node*)object;
    sender->stopAllActions();
    MoveTo *moveTo = MoveTo::create(1.0, Vec2(60, 320));
    CallFuncN *funcND = CallFuncN::create(CC_CALLBACK_0(Bullet::moveSunshine,this, sender->getParent()));
    Sequence *seq = Sequence::create(moveTo,funcND,NULL);
    sender->getParent()->runAction(seq);
}




void Bullet::creatHeroPeaBullet(Point p, Layer *layer)
{
	position = p;
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("PeashooterBullet_default.plist");
	this->initWithSpriteFrameName("PeashooterBullet.tiff");
	this->setPosition(Vec2(p.x +10, p.y + 10));
	this->setScale(0.5);
	/*cout << &bulletArray;*/
	GameScene2::bulletArray.pushBack(this);//把子弹添加到数组里边
	layer->addChild(this);
	float distance = 500 - this->getPosition().x;
	float time = distance / BulletSpeedRatio;//子弹速度 （时间＝距离／子弹速度）
	MoveTo *moveTo = MoveTo::create(time, Vec2(500, this->getPosition().y));
	this->runAction(moveTo);
}
Bullet::Bullet(hero *aplants, Point p, Layer *layer)
{
	//hero_temp = new hero(aplants->type);
	switch (aplants->type)
	{
	case hero1:
		this->damage = 30;
		this->creatHeroPeaBullet(p, layer);
		break;
	case hero2:
		this->damage = 40;
		this->creatHeroPeaBullet(p, layer);
		break;
	case hero3:
		this->damage = 45;
		this->creatHeroPeaBullet(p, layer);
		break;
	default:
		this->damage = 45;
		this->creatHeroPeaBullet(p, layer);
		break;
	}
}













