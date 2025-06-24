#include "MonsterDecorator.h"

MonsterDecorator::MonsterDecorator(std::unique_ptr<Monster> m)
	: monster(std::move(m)) {}

std::string MonsterDecorator::getName() const 
{
	return monster->getName();
}

int MonsterDecorator::getHealth() const 
{
	return monster->getHealth();
}

int MonsterDecorator::getAttack() const 
{
	return monster->getAttack();
}

void MonsterDecorator::takeDamage(int damage) 
{
	monster->takeDamage(damage);
}

int MonsterDecorator::getExpReward() const 
{
	return monster->getExpReward();
}

int MonsterDecorator::getGoldReward() const
{
	return monster->getGoldReward();
}