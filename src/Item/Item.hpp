#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

using namespace std;

enum ItemType {
    BUILDING,
    PLANT,
    ANIMAL,
    PRODUCT,
    RECIPE
};

class Item {
    protected:
        int itemID;
        string itemCode;
        string itemName;
        int itemPrice;
        ItemType itemType;
    public:
        Item();

        Item(int itemID, const string& itemCode, const string& itemName, int itemPrice, ItemType itemType);
        
        virtual ~Item(); // virtual dtor

        // getters
        int getItemID() const;
        string getItemCode() const;
        string getItemName() const;
        int getItemPrice() const;
        ItemType getItemType() const;

        // setters
        void setItemID(int newItemID);
        void setItemCode(const string& newItemCode);
        void setItemName(const string& newItemName);
        void setItemPrice(int newItemPrice);
        void setItemType(ItemType newItemType);

        // operator overloads
        bool operator==(const Item& other) const;
        bool operator<(const Item& other) const;

        // polymorphic behavior
        virtual void displayItem() const = 0; // display each item differently
        virtual Item* cloneItem() const = 0; // create copies tanpa tau tipe objeknya
};

#endif
