#include "Item.hpp"

// ctor
Item::Item(int itemID, const std::string& itemCode, const std::string& itemName, int itemPrice, ItemType itemType)
    : itemID(itemID), itemCode(itemCode), itemName(itemName), itemPrice(itemPrice), itemType(itemType) {}

// virtual dtor
Item::~Item() {}


// getters
int Item::getItemID() const { return itemID; }
std::string Item::getItemCode() const { return itemCode; }
std::string Item::getItemName() const { return itemName; }
int Item::getItemPrice() const { return itemPrice; }
ItemType Item::getItemType() const { return itemType; }


// setters
void Item::setItemID(int newID) { itemID = newID; }
void Item::setItemCode(const std::string& newCode) { itemCode = newCode; }
void Item::setItemName(const std::string& newName) { itemName = newName; }
void Item::setItemPrice(int newPrice) { itemPrice = newPrice; }
void Item::setItemType(ItemType newItemType) { itemType = newItemType; }


// operator overloads implementation
bool Item::operator==(const Item& other) const {
    return itemID == other.itemID;
}
bool Item::operator<(const Item& other) const {
    return itemID < other.itemID;
}


// polymorphic behavior
void Item::displayItem() const {
    std::string typeName;
    switch (itemType) {
        case BUILDING: typeName = "Building"; break;
        case PLANT:    typeName = "Plant";    break;
        case ANIMAL:   typeName = "Animal";   break;
        case PRODUCT:  typeName = "Product";  break;
    }
    std::cout << "Type: " << typeName << ", ID: " << itemID << ", Code: " << itemCode << ", Name: " << itemName << ", Price: " << itemPrice << std::endl;
}

// Item* Item::cloneItem() const {
//     // harus dioverride sama derived class
//     // throw std::logic_error("Clone not implemented for base Item");
// }