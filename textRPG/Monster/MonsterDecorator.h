#pragma once
#include "Monster.h"
#include <memory>


class MonsterDecorator : public Monster
{
protected:
	std::unique_ptr<Monster> monster;

public:
	MonsterDecorator(std::unique_ptr<Monster> m);

	std::string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	int getExpReward() const override;      
	int getGoldReward() const override;     

	virtual ~MonsterDecorator() = default;
};
