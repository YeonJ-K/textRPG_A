#include "BossDecorator.h"
#include <iostream>
BossDecorator::BossDecorator(std::unique_ptr<Monster> m)
	: MonsterDecorator(std::move(m))
{
	bossHealth = static_cast<int>(std::round(monster->getHealth()*1.5));
	bossAttack = static_cast<int>(std::round(monster->getAttack()*1.5));
	std::cout<<"최고레벨에 도달하여 보스 몬스터가 소환됩니다.\n";
}

std::string BossDecorator::getName() const 
{
	return monster->getName()+" King";
}

int BossDecorator::getHealth() const 
{
	return bossHealth;
}

int BossDecorator::getAttack() const 
{
	return bossAttack;
}

void BossDecorator::takeDamage(int damage) 
{
	bossHealth = std::max(0, bossHealth-damage);
}

int BossDecorator::getExpReward() const //보스 클리어 시 게임 종료
{
	return 0;  
}

int BossDecorator::getGoldReward() const
{
	return 0;
}
