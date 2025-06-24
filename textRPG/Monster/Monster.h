#pragma once
#include <string>
//몬스터 인터페이스	정의
class Monster
{
public:
	virtual std::string getName() const = 0;
	virtual void takeDamage(int damage) = 0;
	virtual int getHealth() const = 0;
	virtual int getAttack() const = 0;
	virtual int getExpReward() const = 0;
	virtual int getGoldReward() const = 0;
	//virtual Item* dropItem() const = 0;

	virtual ~Monster() = default;
};
