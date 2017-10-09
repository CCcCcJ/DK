//
//  Bullet.h
//  PlantsVSZombies
//
//  Created by user on 13-6-5.
//
//

#ifndef __PlantsVSZombies__Bullet__
#define __PlantsVSZombies__Bullet__

#include <iostream>
#include "cocos2d.h"
#include"GameScene2.h"
#include "hero.h"
using namespace cocos2d;
using namespace std;
#define BulletSpeedRatio 200 //子弹速度 （时间＝距离／子弹速度）
//typedef enum
//{
//	bullet1 = 0,
//	bullet2,
//	bullet3,
//
//}bulletType;
class Bullet:public Sprite
{
public:
	//bulletType tyep;
    Point position;
	int damage;
public:
	Bullet(hero *aplants, Point p, Layer *layer);
    ~Bullet();
	void creatHeroPeaBullet(Point p, Layer*layer);
    void collectSunshine(Ref *sender);
    void moveSunshine(Node *sender);
};
#endif
/* defined(__PlantsVSZombies__Bullet__) */



