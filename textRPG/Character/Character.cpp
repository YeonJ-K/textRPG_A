#include "Character.h"
#include "item.h"

Character* Character::instance = nullptr;

Character::Character(std::string name)
{
	this->name = name;
	level = 1;
	maxHealth = 100;
	health = maxHealth;
	attack = 30;
	experience = 0;
	gold = 0;
}

Character* Character::getInstance(std::string name)
{
	if (instance == nullptr)
	{
		instance = new Character(name);
	}
	return instance;
}

void Character::displayStatus() const
{
	std::cout << "-----------------------\n"
		<< "Character's Name: " << name << '\n'
		<< "Level: " << level << '\n'
		<< "HP: " << health << " / " << maxHealth << '\n'
		<< "Attack: " << attack << '\n'
		<< "EXP: " << experience << '\n'
		<< "Gold: " << gold << '\n'
		<< "-----------------------\n";
}

void Character::levelUp()
{
	while (experience>=100)
	{
		if (level==10)
		{
			std::cout<<"Maximum level reached! (Level 10)!\n";
			experience = 0;
			break;
		}

		experience -= 100;
		++level;

		maxHealth += (level * 20);
		health = maxHealth;
		attack += (level * 5);

		std::cout<<"Level Up! Current Level / Experience: "
			<<level<<"Lv / "<<experience<<'\n';
	}
}


void Character::takeDamage(int damage)
{
	health = std::max(0, health-damage);
}

int Character::getAttack() const
{
	return attack;
}

int Character::getHealth() const
{
	return health;
}

int Character::getMaxHealth() const
{
	return maxHealth;
}

int Character::getLevel() const
{
	return level;
}

std::string Character::getName() const
{
	return name;
}

void Character::useItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        auto& invItem = inventory[index];
        if (invItem.item && invItem.quantity > 0) {
            invItem.item->use(*this);

            if (invItem.item->isConsumable()) {
                invItem.quantity--;
                std::cout << invItem.item->name << " 사용! 남은 수량: " << invItem.quantity << "\n";

                if (invItem.quantity == 0) {
                    delete invItem.item;
                    inventory.erase(inventory.begin() + index);
                    std::cout << "→ 아이템이 모두 소진되어 인벤토리에서 제거됩니다.\n";
                }
            }
        }
    } else {
        std::cout << "잘못된 아이템 인덱스입니다.\n";
    }
}
{
	if (index >= 0 && index < inventory.size())
	{
		if (inventory[index] != nullptr)
		{
			// 인벤토리 사용 후 삭제
			// TODO: 인벤토리의 아이템 사용(Item::use())

			delete inventory[index];
			inventory[index] = nullptr;
		}
		else
		{
			std::cout << "Error: There are no items in Inventory." << '\n';
		}
	}
	else
	{
		std::cout << "Error: Invalid item index." << '\n';
	}
}

void Character::addExperience(int exp) 
{
	experience += exp; 
	levelUp();
}
void Character :: addGold(int gol) 
{ 
	gold += gol;
}

// 주사위 아이템 사용
bool rollForEvade() {
	if (hasMissDice) {
		int roll = std::rand() % 6 + 1;
		std::cout << "[회피 주사위] 주사위 결과: " << roll << std::endl;
		if (roll == 3) {
			std::cout << "→ 회피 성공! 피해를 받지 않습니다!\n";
			return true;
		}
	}
	return false;
}

void rollSnackRecovery() {
	if (hasSnacks) {
		int roll = std::rand() % 6 + 1;
		std::cout << "[간식 주사위] 주사위 결과: " << roll << std::endl;
		if (roll == 1) {
			hp = std::min(hp + 3, maxHp);
			std::cout << "→ 간식 효과 발동! 체력을 3 회복했습니다. 현재 체력: " << hp << "/" << maxHp << "\n";
		}
	}
}

void Character::visitShop()
{
	int choice = 0;
	std::cout<<"상점을 이용하시겠습니까?\n";
	std::cout<<"1. 예\n2. 아니오\n";

	while (true)
	{
		std::cin>>choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout<<"잘못된 입력입니다. 숫자로 입력해주세요.\n> ";
			continue;
		}

		if (choice==1)
		{
			std::cout<<"상점에 오신 것을 환영합니다!\n\n";
			std::cout << "[상점 입장] 다음 아이템들을 판매 중입니다:";
			std::cout << "- 자동차 에어백 (180G): 어떤 공격이라도 5의 데미지만 받습니다.";
			std::cout << "- 쌍절곤 (120G): 한 턴 동안 두 번 공격합니다.";
			std::cout << "- 가시채찍 (80G): 체력 5 소모 후 공격력의 2~15% 데미지를 줍니다.";
			std::cout << "- 근육증진물약 (150G): 공격력 +10 영구 증가.";
			std::cout << "- 튼튼물약 (150G): 최대 체력 +20 영구 증가.";
			std::cout << "- 회피 주사위 (400G): 매 턴 3이 나오면 공격 회피.";
			std::cout << "- 비상용 간식 (350G): 매 턴 1이 나오면 체력 +3 회복." << std::endl;

			while (true) {
				std::cout << "\n===== 상점 =====\n";
				for (size_t i = 0; i < items.size(); ++i) {
					std::cout << i + 1 << ". " << items[i]->name << " - " << items[i]->price << "G\n";
				}
				std::cout << "0. 나가기\n현재 골드: " << player.gold << "\n구매할 번호 선택: ";
				int choice;
				std::cin >> choice;
				if (choice == 0) break;
				if (choice < 1 || choice > static_cast<int>(items.size())) continue;
				auto item = items[choice - 1];
				if (item->price > player.gold) {
					std::cout << "골드가 부족합니다.\n";
					continue;
				}
				if (item->isUnique()) {
					if ((item->name == "회피 주사위" && player.hasMissDice) ||
						(item->name == "비상용 간식" && player.hasSnacks)) {
						std::cout << "이 아이템은 한 번만 구매할 수 있습니다.\n";
						continue;
						}
				}
				player.gold -= item->price;
				inventory.push_back(item);
				item->use(player);
			}

			break; // 상점 입장
		}
		else if (choice==2)
		{
			std::cout<<"상점을 이용하지 않습니다.\n";
			return; // 함수 종료
		}
		else
		{
			std::cout<<"잘못된 선택입니다. 다시 선택해주세요.\n> ";
		}
	}
	//상점 구현
	std::cout<<"상점 기능은 아직 구현되지 않았습니다.\n";
}
