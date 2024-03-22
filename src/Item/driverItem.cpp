#include "Item.hpp"
#include <vector>
#include <memory>


class DummyItem : public Item {
public:
    DummyItem(int itemID, const std::string& itemCode, const std::string& itemName, int itemPrice, ItemType itemType)
        : Item(itemID, itemCode, itemName, itemPrice, itemType) {}

    virtual void displayItem() const override {
        std::cout << "Displaying DummyItem: " << std::endl;
        Item::displayItem(); 
    }

    virtual Item* cloneItem() const override {
        return new DummyItem(*this); 
    }
};


int main() {
    std::vector<std::unique_ptr<Item>> items;

    items.push_back(std::make_unique<DummyItem>(1, "sav", "Dummy Item 1", 9.99, ItemType::PRODUCT));
    items.push_back(std::make_unique<DummyItem>(2, "age", "Dummy Item 2", 19.99, ItemType::ANIMAL));

    for (const auto& item : items) {
        item->displayItem();
    }

    std::unique_ptr<Item> clonedItem(items[0]->cloneItem());
    std::cout << "Cloned Item: " << std::endl;
    clonedItem->displayItem();

    return 0;
}


// HOW TO RUN
// g++ -o driverItem Item.cpp driverItem.cpp
// ./driverItem