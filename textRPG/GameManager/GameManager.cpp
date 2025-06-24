#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "../item.h"
#include <random>
#include <memory>
#include <iostream>

void GameManager::battle(Character* player, std::unique_ptr<Monster> monster) {
	std::string monsterName = monster->getName();
	std::string characterName = player->getName();

	std::cout<<"전투 시작! "<<monsterName<<" 이(가) 나타났다!\n";
	std::cout<<monsterName<<"'s HP: "<<monster->getHealth()<<"\n";
	std::cout<<monsterName<<"'s Attack: "<<monster->getAttack()<<"\n\n";

	while (player->getHealth()>0&&monster->getHealth()>0) {
		player->rollForSnackRecovery();

		char action;
		std::cout<<"무엇을 하시겠습니까? (a: 공격 / i: 아이템 사용): ";
		std::cin>>action;

		if (action=='i') {
			std::cout<<"[보유 중인 아이템 목록]\n";
			for (size_t i = 0; i<player->inventory.size(); ++i) {
				if (player->inventory[i].item&&player->inventory[i].quantity>0) {
					std::cout<<i<<". "<<player->inventory[i].item->name<<" (x"<<player->inventory[i].quantity<<")\n";
				}
			}
			int idx;
			std::cout<<"사용할 아이템 인덱스를 입력하세요: ";
			std::cin>>idx;
			player->useItem(idx);
		}

		std::cout<<">> "<<characterName<<"의 공격!\n";
		monster->takeDamage(player->getAttack());
		std::cout<<monsterName<<"'s HP: "<<monster->getHealth()<<"\n\n";

		if (monster->getHealth()<=0) {
			std::cout<<monsterName<<" 을(를) 처치했다!\n";
			break;
		}

		std::cout<<">> "<<monsterName<<"의 공격!\n";
		bool evaded = player->rollForEvade();
		if (!evaded) {
			player->takeDamage(monster->getAttack());
			std::cout<<characterName<<"'s HP: "<<player->getHealth()<<"\n\n";
		}
		else {
			std::cout<<characterName<<"이(가) 공격을 회피했습니다!\n\n";
		}

		if (player->getHealth()<=0) {
			std::cout<<characterName<<"이(가) 쓰러졌습니다. 게임 종료.\n";
			exit(0);
		}
	}

	std::cout<<"전투 종료.\n";

	std::cout<<">> "<<characterName<<"이(가) "<<monster->getExpReward()<<" 경험치를 얻었습니다!\n";
	player->addExperience(monster->getExpReward());

	int gold = 20+std::rand()%21; // 20~40 골드
	std::cout<<">> "<<characterName<<"이(가) "<<gold<<" 골드를 얻었습니다!\n\n";
	player->addGold(gold);

	char shopChoice;
	std::cout<<"상점에 입장하시겠습니까? (y/n): ";
	std::cin>>shopChoice;
	if (shopChoice=='y'||shopChoice=='Y') {
		std::cout<<"현재 보유 골드: "<<player->getGold()<<"G";
		std::cout<<"\n[상점 목록]\n";
		std::cout<<"0. 자동차 에어백 (180G)\n";
		std::cout<<"1. 쌍절곤 (120G)\n";
		std::cout<<"2. 가시채찍 (80G)\n";
		std::cout<<"3. 근육증진물약 (150G)\n";
		std::cout<<"4. 튼튼물약 (150G)\n";
		std::cout<<"5. 회피 주사위 (400G)\n";
		std::cout<<"6. 비상용 간식 (350G)\n";

		int choice;
		std::cout<<"구매할 아이템 번호를 입력하세요: ";
		std::cin>>choice;

		switch (choice) {
		case 0:
			if (player->canAfford(180)) {
				player->addGold(-180);
				player->addItem(new item_airBag(), 1);
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		case 1:
			if (player->canAfford(120)) {
				player->addGold(-120);
				player->addItem(new item_ssangbong(), 1);
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		case 2:
			if (player->canAfford(80)) {
				player->addGold(-80);
				player->addItem(new item_thornWhip(), 1);
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		case 3:
			if (player->canAfford(150)) {
				player->addGold(-150);
				player->addItem(new item_attackPotion(), 1);
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		case 4:
			if (player->canAfford(150)) {
				player->addGold(-150);
				player->addItem(new item_healthPotion(), 1);
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		case 5:
			if (player->hasMissDice) {
				std::cout<<"이미 회피 주사위를 보유하고 있습니다.\n";
			}
			else if (player->canAfford(400)) {
				player->addGold(-400);
				player->addItem(new item_missDice(), 1);
				player->hasMissDice = true;
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		case 6:
			if (player->hasSnacks) {
				std::cout<<"이미 비상용 간식을 보유하고 있습니다.\n";
			}
			else if (player->canAfford(350)) {
				player->addGold(-350);
				player->addItem(new item_snacks(), 1);
				player->hasSnacks = true;
			}
			else std::cout<<"골드가 부족합니다.\n";
			break;
		default:
			std::cout<<"잘못된 입력입니다.\n";
		}
	}
}
