#include "item.h"
#include <algorithm>
#include <cstdlib>

// DropItem 구현
DropItem::DropItem(std::string _name, int _heal) : healAmount(_heal) {
    name = _name;
    price = 0;
}

void DropItem::use(Player& player) {
    player.hp = std::min(player.hp + healAmount, player.maxHp);
    std::cout << "[" << name << "] 체력 +" << healAmount << " 회복! 현재 체력: " << player.hp << std::endl;
}

bool DropItem::isConsumable() const { return true; }

// item_airBag
item_airBag::item_airBag() { name = "자동차 에어백"; price = 180; }

void item_airBag::use(Player&) {
    std::cout << "[에어백 사용] 이번 턴 모든 피해를 5로 제한합니다.\n";
}

bool item_airBag::isConsumable() const { return true; }

// item_ssangbong
item_ssangbong::item_ssangbong() { name = "쌍절곤"; price = 120; }

void item_ssangbong::use(Player&) {
    std::cout << "[쌍절곤 사용] 이번 턴 두 번 공격합니다!\n";
}

bool item_ssangbong::isConsumable() const { return true; }

// item_thornWhip
item_thornWhip::item_thornWhip() { name = "가시채찍"; price = 80; }

void item_thornWhip::use(Player& player) {
    if (player.hp <= 5) {
        std::cout << "[가시채찍 실패] 체력이 부족합니다!\n";
        return;
    }
    player.hp -= 5;
    int percent = std::rand() % 14 + 2;
    int damage = player.atk * percent / 100;
    std::cout << "[가시채찍 사용] 체력 5를 희생하고 추가 피해 " << damage << "를 줍니다!\n";
}

bool item_thornWhip::isConsumable() const { return true; }

// item_attackPotion
item_attackPotion::item_attackPotion() { name = "근육증진물약"; price = 150; }

void item_attackPotion::use(Player& player) {
    player.atk += 10;
    std::cout << "[근육증진물약] 공격력 +10! 현재 공격력: " << player.atk << std::endl;
}

bool item_attackPotion::isConsumable() const { return false; }

// item_healthPotion
item_healthPotion::item_healthPotion() { name = "튼튼물약"; price = 150; }

void item_healthPotion::use(Player& player) {
    player.maxHp += 20;
    player.hp += 20;
    std::cout << "[튼튼물약] 체력 +20! 현재 체력: " << player.hp << "/" << player.maxHp << std::endl;
}

bool item_healthPotion::isConsumable() const { return false; }

// item_missDice
item_missDice::item_missDice() { name = "회피 주사위"; price = 400; }

void item_missDice::use(Player& player) {
    player.hasMissDice = true;
    std::cout << "[회피 주사위] 매 턴 3이 나오면 공격 회피 가능!\n";
}

bool item_missDice::isConsumable() const { return false; }
bool item_missDice::isUnique() const { return true; }

// item_snacks
item_snacks::item_snacks() { name = "비상용 간식"; price = 350; }

void item_snacks::use(Player& player) {
    player.hasSnacks = true;
    std::cout << "[비상용 간식] 매 턴 1이 나오면 체력 +3 회복!\n";
}

bool item_snacks::isConsumable() const { return false; }
bool item_snacks::isUnique() const { return true; }

// 드랍 아이템 생성 함수
std::shared_ptr<Item> getDropItem() {
    int roll = std::rand() % 100;
    if (roll < 40) return std::make_shared<DropItem>("소형물약", 10); // 40%
    else if (roll < 60) return std::make_shared<DropItem>("중형물약", 30); // 20%
    else return nullptr;
}
