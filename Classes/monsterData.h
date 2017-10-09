#ifndef  MONSTERDATA_H_
#define  MONSTERDATA_H_
#include "monster.h"
class MonsterData :public Ref
{
private:
	MonsterType monstertype;
	int _lifeValue;
	int _gold;
public :
	static MonsterData* create();

	void  setmonstertype(std::string name);

	MonsterType getmonstertype();
	
};
#endif // ! MONSTERDATA_H_
