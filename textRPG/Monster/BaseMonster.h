#pragma once
#include "Monster.h"
#include <random>
class BaseMonster : public Monster
{
private:
	int health;
	int attack;
	std::string name;
	int expReward;
	int goldReward;
	int getRandomInRange(int min, int max) const;

public:
	BaseMonster(int level, std::string name);
	std::string getName() const override;
	void takeDamage(int damage) override;
	int getHealth() const override;
	int getAttack() const override;
	int getExpReward() const override;
	int getGoldReward() const override;
};
