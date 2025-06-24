#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../item.h"

class Item;

struct InventoryItem {
	Item* item;
	int quantity;
};

class Character {
private:
	static Character* instance;

	std::string name;
	int level;
	int maxHealth;
	int health;
	int attack;
	int experience;
	int gold;

public:
	bool hasSnacks;
	bool hasMissDice;
	std::vector<InventoryItem> inventory;

	Character(std::string name);
	static Character* getInstance(std::string name = "");

	void displayStatus() const;
	void levelUp();
	void useItem(int index);
	void visitShop();

	int getHealth() const;
	int getMaxHealth() const;
	int getAttack() const;
	int getLevel() const;
	std::string getName() const;
	int getGold() const;

	void takeDamage(int damage);
	void addExperience(int exp);
	void addGold(int gol);

	void rollForSnackRecovery();
	bool rollForEvade();
	bool canAfford(int price) const;
	void addItem(Item* item, int quantity);
};
