#include "Item.hpp"
#include <stdexcept>
#include <vector>


class DummyItem : public Item {
public:
    DummyItem(int itemID, const std::string& itemCode, const std::string& itemName, int itemPrice)
        : Item(itemID, itemCode, itemName, itemPrice) {}

    virtual void displayItem() const override {
        Item::displayItem(); // base class display
        std::cout << "This is a DummyItem display." << std::endl;
    }

    virtual Item* cloneItem() const override {
        return new DummyItem(*this);
    }
};

int main() {
    // create a vector of Item pointers for polymorphism
    std::vector<Item*> items;

    // create dummy items
    items.push_back(new DummyItem(1, "sav", "dummy item 1", 9.99));
    items.push_back(new DummyItem(2, "age", "dummy item 2", 19.99));

    // display items using polymorphism
    for (const auto& item : items) {
        item->displayItem();
    }

    // clone dummy item 1
    Item* clonedItem = items[0]->cloneItem();
    clonedItem->displayItem();

    // clean up dynamic memory
    for (auto& item : items) {
        delete item;
    }
    delete clonedItem;

    return 0;
}
