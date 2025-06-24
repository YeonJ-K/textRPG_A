#pragma once
#include "MonsterDecorator.h"
#include <string>
#include <cmath>

class BossDecorator : public MonsterDecorator
{
private:
	int bossHealth;
	int bossAttack;

public:
	BossDecorator(std::unique_ptr<Monster> m);

	std::string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;

	int getExpReward() const override;
	int getGoldReward() const override;
};
