#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

class Item {
protected:
    int itemID;
    std::string itemCode;
    std::string itemName;
    int itemPrice;

public:
    Item(int itemID, const std::string& itemCode, const std::string& itemName, int itemPrice);
    virtual ~Item(); // virtual dtor

    // getters
    int getItemID() const;
    std::string getItemCode() const;
    std::string getItemName() const;
    int getItemPrice() const;

    // setters
    void setItemID(int newItemID);
    void setItemCode(const std::string& newItemCode);
    void setItemName(const std::string& newItemName);
    void setItemPrice(int newItemPrice);

    // operator overloads
    bool operator==(const Item& other) const;
    bool operator<(const Item& other) const;

    // polymorphic behavior
    virtual void displayItem() const = 0; // display each item differently
    virtual Item* cloneItem() const = 0; // create copies tanpa tau tipe objeknya
};

#endif // ITEM_HPP
