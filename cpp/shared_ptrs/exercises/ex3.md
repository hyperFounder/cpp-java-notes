# Exclusive Ownership Exercise  
**Game Inventory System (`unique_ptr` + raw observer pointer)**

## Goal
Train the correct mental model for **exclusive ownership** using `std::unique_ptr`:
- exactly **one owner**
- ownership can be **moved**
- no copying
- deterministic destruction

---

## The Scenario: The Player and the Items

### The Player
- Exclusively owns a collection of Items  
- If the Player is destroyed, all Items must be destroyed immediately  
- **Exclusive ownership** (`unique_ptr`)

### The Item
- Needs to know which Player currently holds it  
- But the Item must **not own** the Player  
- Since `unique_ptr` has no `weak_ptr`, the Item stores a **non-owning raw pointer** (`Player*`)  
- This pointer must never be dereferenced after the Player is gone

---

## Your Exercise: The Inventory System

### Task
Write the C++ code for two classes:

- **Item**
  - Contains a `std::string name`
  - Contains a `Player* owner` (non-owning observer pointer)
  - Has `inspect()` method

- **Player**
  - Contains a `std::string name`
  - Contains a `std::vector<std::unique_ptr<Item>> inventory`
  - Has `pickup(std::unique_ptr<Item> item)` method (moves ownership into inventory)

---

## The Goal

Implement `inspect()` in `Item`.

- If `owner != nullptr`, print:  
  **`Inspecting [Item] (owned by [Player])`**
- If `owner == nullptr`, print:  
  **`Inspecting [Item] (unowned)`**

Also implement `pickup()` in `Player`.

- It must:
  - set `item->owner = this`
  - move the item into `inventory`

---

## Visualizing the Ownership

- Player → Item : `unique_ptr` (exclusive ownership)
- Item → Player : raw pointer (observer only)
- Ownership can move: you must use `std::move`

---

## Starting Template (Assume C++11)

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Player; // Forward declaration

class Item {
public:
    std::string name;
    // TODO: Add a raw observer pointer to Player (Player* owner)

    Item(std::string n) : name(n) {}

    void inspect() {
        // TODO: If owner != nullptr print:
        // "Inspecting [Item] (owned by [Player])"
        // TODO: Else print:
        // "Inspecting [Item] (unowned)"
    }
};

class Player {
public:
    std::string name;
    // TODO: Add a vector of unique_ptr<Item> inventory

    Player(std::string n) : name(n) {}
    ~Player() { std::cout << "Player " << name << " destroyed.\n"; }

    void pickup(std::unique_ptr<Item> item) {
        // TODO:
        // 1) Set item's owner = this
        // 2) Move item into inventory (std::move)
    }
};

int main() {
    // TODO: 1) Create a Player using std::unique_ptr<Player>

    // TODO: 2) Create an Item using std::unique_ptr<Item>

    // TODO: 3) Call inspect() (should say unowned)

    // TODO: 4) Player picks up the item (must use std::move)

    // TODO: 5) Inspect item through player's inventory (should show owner)

    // TODO: 6) Reset/destroy the Player unique_ptr

    // TODO: 7) Program ends; confirm destructors make sense

    return 0;
}
