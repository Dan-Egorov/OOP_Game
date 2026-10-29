#pragma once
#include <vector>
#include <memory>
#include "../Item/item.hpp"

class Inventory {
private:
    std::vector<std::shared_ptr<Item>> items;
public:
    void addItem(std::shared_ptr<Item> item) { items.push_back(item); }
    const std::vector<std::shared_ptr<Item>>& getItems() const { return items; }

    void removeItem(int index) {
        if (index >= 0 && index < items.size()) {
            items.erase(items.begin() + index);
        }
    }
};