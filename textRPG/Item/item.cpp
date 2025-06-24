#include "item.h"
#include "Character.h"
#include <iostream>
#include <cstdlib>

void item_airBag::use(Character& character) {
	std::cout<<"에어백 사용: 이번 턴 받는 피해는 최대 5로 제한됩니다! (구현 생략)\n";
}

void item_ssangbong::use(Character& character) {
	std::cout<<"쌍절곤 사용: 이번 턴 2번 공격합니다! (구현 생략)\n";
}

void item_thornWhip::use(Character& character) {
	character.takeDamage(5);
	int percent = 2+std::rand()%14; // 2~15%
	int extra = character.getAttack()*percent/100;
	std::cout<<"가시채찍 사용! 체력 -5, 추가 데미지 "<<extra<<"를 적에게 줍니다!\n";
}

void item_attackPotion::use(Character& character) {
	std::cout<<"공격력이 영구적으로 10 증가했습니다!\n";
}

void item_healthPotion::use(Character& character) {
	std::cout<<"최대 체력이 영구적으로 20 증가했습니다!\n";
}

void item_missDice::use(Character& character) {
	character.hasMissDice = true;
	std::cout<<"회피 주사위를 장착했습니다. 매 턴 3이 나오면 공격을 회피합니다.\n";
}

void item_snacks::use(Character& character) {
	character.hasSnacks = true;
	std::cout<<"비상용 간식을 장착했습니다. 매 턴 1이 나오면 체력 +3 회복됩니다.\n";
}
