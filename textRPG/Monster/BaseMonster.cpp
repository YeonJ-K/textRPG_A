#include "BaseMonster.h"

int BaseMonster::getRandomInRange(int min, int max) const 
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

BaseMonster::BaseMonster(int level, std::string name)
	: health(getRandomInRange(level*20, level*30)),
	attack(getRandomInRange(level*5, level*10)),
	expReward(50),
	goldReward(getRandomInRange(10, 20)),
	name(name){}

std::string BaseMonster::getName() const 
{
	return name;
}

void BaseMonster::takeDamage(int damage) 
{
	health = std::max(0, health-damage);
}

int BaseMonster::getHealth() const
{
	return health;
}

int BaseMonster::getAttack() const
{
	return attack;
}
int BaseMonster::getExpReward() const
{
	return expReward;  
}

int BaseMonster::getGoldReward() const
{
	return goldReward;  
}	