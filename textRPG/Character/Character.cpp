#include "Character.h"
#include "../item.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

Character* Character::instance = nullptr;

Character::Character(std::string name)
	: name(name), level(1), maxHealth(100), health(100), attack(10),
	experience(0), gold(300), hasSnacks(false), hasMissDice(false) {
}

Character* Character::getInstance(std::string name) {
	if (!instance) {
		instance = new Character(name);
	}
	return instance;
}


void Character::displayStatus() const {
	std::cout<<"[플레이어 상태]\n";
	std::cout<<"이름: "<<name 
		<< " | 레벨: "<<level
		<<" | 체력: "<<health<<"/"<<maxHealth
		<<" | 공격력: "<<attack
		<<" | 경험치: "<<experience
		<<" | 골드: "<<gold<<"\n";
}

void Character::levelUp() {
	level++;
	maxHealth += 20;
	health = maxHealth;
	attack += 5;
	std::cout<<name<<"의 레벨이 "<<level<<"로 올랐습니다!\n";
}

void Character::useItem(int index) {
	if (index>=0&&index<inventory.size()) {
		auto& invItem = inventory[index];
		if (invItem.item&&invItem.quantity>0) {
			invItem.item->use(*this);
			if (invItem.item->isConsumable()) {
				invItem.quantity--;
				std::cout<<invItem.item->name<<" 사용! 남은 수량: "<<invItem.quantity<<"\n";
				if (invItem.quantity==0) {
					delete invItem.item;
					inventory.erase(inventory.begin()+index);
					std::cout<<"→ 아이템이 모두 소진되어 인벤토리에서 제거됩니다.\n";
				}
			}
		}
	}
	else {
		std::cout<<"잘못된 아이템 인덱스입니다.\n";
	}
}

void Character::visitShop() {
	std::cout<<"[상점 기능은 아직 구현되지 않았습니다]\n";
}

int Character::getHealth() const { return health; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getLevel() const { return level; }
std::string Character::getName() const { return name; }
int Character::getGold() const { return gold; }

void Character::takeDamage(int damage) {
	health -= damage;
	if (health<0) health = 0;
}

void Character::addExperience(int exp) {
	experience += exp;
	if (experience>=100) {
		experience -= 100;
		levelUp();
	}
}

void Character::addGold(int gol) {
	gold += gol;
}

bool Character::canAfford(int price) const {
	return gold>=price;
}

void Character::addItem(Item* item, int quantity) {
	for (auto& inv:inventory) {
		if (inv.item->name==item->name) {
			inv.quantity += quantity;
			return;
		}
	}
	inventory.push_back({ item, quantity });
}


void Character::rollForSnackRecovery() {
	if (hasSnacks) {
		int roll = std::rand()%6+1;
		if (roll==1) {
			health = std::min(health+3, maxHealth);
			std::cout<<"비상용 간식 효과! 체력 +3 회복됨! 현재 체력: "<<health<<"/"<<maxHealth<<"\n";
		}
	}
}

bool Character::rollForEvade() {
	if (hasMissDice) {
		int roll = std::rand()%6+1;
		return roll==3;
	}
	return false;
}
