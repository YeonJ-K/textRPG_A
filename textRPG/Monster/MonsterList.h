#pragma once
#include "BaseMonster.h"


class Goblin : public BaseMonster
{
public:
	Goblin(int level);
};

class Orc : public BaseMonster
{
public:
	Orc(int level);
};

class Troll : public BaseMonster
{
public:
	Troll(int level);
};

class Slime : public BaseMonster
{
public:
	Slime(int level);

};

class Dragon : public BaseMonster
{
public:
	Dragon(int level);
};
