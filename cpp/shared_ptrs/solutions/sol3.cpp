#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Player; // Forward declaration

class Item {
public:
    std::string name;
    Player* owner; // non-owning observer pointer

    Item(const std::string& n) : name(n), owner(nullptr) {}

    void inspect() const;
};

class Player {
public:
    std::string name;
    std::vector<std::unique_ptr<Item>> inventory; // exclusive ownership

    Player(const std::string& n) : name(n) {}
    ~Player() { std::cout << "Player " << name << " destroyed.\n"; }

    void pickup(std::unique_ptr<Item> item) {
        item->owner = this;                 // set observer pointer
        inventory.push_back(std::move(item)); // move ownership into inventory
    }
};

void Item::inspect() const {
    if (owner) {
        std::cout << "Inspecting " << name << " (owned by " << owner->name << ")\n";
    } else {
        std::cout << "Inspecting " << name << " (unowned)\n";
    }
}

int main() {
    // 1) Create a Player using unique_ptr
    auto player = std::make_unique<Player>("Alice");

    // 2) Create an Item using unique_ptr
    auto item = std::make_unique<Item>("Excalibur");

    // 3) Inspect (unowned)
    item->inspect();

    // 4) Player picks up the item (must move)
    player->pickup(std::move(item));

    // 5) Inspect through player's inventory (owned by Alice)
    player->inventory[0]->inspect();

    // 6) Destroy the Player (inventory items destroyed too)
    player.reset();

    return 0;
}
