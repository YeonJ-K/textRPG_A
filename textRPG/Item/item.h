 #ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <memory>
#include <string>

class Player;

class Item {
public:
    std::string name;
    int price;
    virtual void use(Player& player) = 0;
    virtual bool isConsumable() const = 0;
    virtual bool isUnique() const { return false; }
    virtual ~Item() {}
};

class DropItem : public Item {
    int healAmount;
public:
    DropItem(std::string _name, int _heal);
    void use(Player& player) override;
    bool isConsumable() const override;
};

// 상점 아이템들 선언
class item_airBag : public Item {
public:
    item_airBag();
    void use(Player& player) override;
    bool isConsumable() const override;
};

class item_ssangbong : public Item {
public:
    item_ssangbong();
    void use(Player& player) override;
    bool isConsumable() const override;
};

class item_thornWhip : public Item {
public:
    item_thornWhip();
    void use(Player& player) override;
    bool isConsumable() const override;
};

class item_attackPotion : public Item {
public:
    item_attackPotion();
    void use(Player& player) override;
    bool isConsumable() const override;
};

class item_healthPotion : public Item {
public:
    item_healthPotion();
    void use(Player& player) override;
    bool isConsumable() const override;
};

class item_missDice : public Item {
public:
    item_missDice();
    void use(Player& player) override;
    bool isConsumable() const override;
    bool isUnique() const override;
};

class item_snacks : public Item {
public:
    item_snacks();
    void use(Player& player) override;
    bool isConsumable() const override;
    bool isUnique() const override;
};

std::shared_ptr<Item> getDropItem();

#endif // ITEM_H
