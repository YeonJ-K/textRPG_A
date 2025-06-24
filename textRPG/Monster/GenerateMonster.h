#pragma once
#include "MonsterList.h"
#include"BossDecorator.h"

enum class MonsterType;

std::unique_ptr<Monster> createMonster(MonsterType type, int level);
std::unique_ptr<Monster> createRandomMonster(int level);