#pragma once
#include "Character.h"
#include "Monster.h"
class GameManager
{
public:
	void effectItem(enum ItemNumber);
	void battle(Character* player, std::unique_ptr<Monster> monster);//캐릭터는 계속 유지, 몬스터는 전투 후 소멸
};

