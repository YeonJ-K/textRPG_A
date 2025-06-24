#pragma once
#include <string>

class Character;

class Item {
public:
	std::string name;
	virtual void use(Character& character) = 0;
	virtual bool isConsumable() const = 0;
	virtual ~Item() = default;
};

// 소모품
class item_airBag : public Item {
public:
	item_airBag() { name = "자동차 에어백"; }
	void use(Character& character) override;
	bool isConsumable() const override { return true; }
};

class item_ssangbong : public Item {
public:
	item_ssangbong() { name = "쌍절곤"; }
	void use(Character& character) override;
	bool isConsumable() const override { return true; }
};

class item_thornWhip : public Item {
public:
	item_thornWhip() { name = "가시채찍"; }
	void use(Character& character) override;
	bool isConsumable() const override { return true; }
};

// 영구 아이템
class item_attackPotion : public Item {
public:
	item_attackPotion() { name = "근육증진물약"; }
	void use(Character& character) override;
	bool isConsumable() const override { return false; }
};

class item_healthPotion : public Item {
public:
	item_healthPotion() { name = "튼튼물약"; }
	void use(Character& character) override;
	bool isConsumable() const override { return false; }
};

class item_missDice : public Item {
public:
	item_missDice() { name = "회피 주사위"; }
	void use(Character& character) override;
	bool isConsumable() const override { return false; }
};

class item_snacks : public Item {
public:
	item_snacks() { name = "비상용 간식"; }
	void use(Character& character) override;
	bool isConsumable() const override { return false; }
};
