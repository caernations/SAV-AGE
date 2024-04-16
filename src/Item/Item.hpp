#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum ItemType {
    BUILDING = 1,
    PLANT,
    ANIMAL,
    PRODUCT,
    RECIPE,
    NUM_ITEM_TYPES

};

class Item {
    protected:
        int itemID;
        string itemCode;
        string itemName;
        int itemPrice;
        ItemType itemType;
    public:
        /**
         * Constructor awal dengan itemID = 0, itemCode = "", itemName = "", itemPrice = 0, itemType = ""
        */
        Item();
        
        /**
         * Constructor dengan parameter
         * @param itemID Kode unik untuk class Item
         * @param itemCode Kode unik untuk class Item
         * @param itemName Nama item
         * @param itemPrice Harga item
         * @param itemType Tipe item
        */
        Item(int itemID, const string& itemCode, const string& itemName, int itemPrice, ItemType itemType);
        
        /**
         * Destructor
        */
        virtual ~Item();

        /**
         * Mengembalikan ID
         * @return itemID
        */
        int getItemID() const;

        /**
         * Mengembalikan kode unik untuk class Item
         * @return itemCode
        */
        string getItemCode() const;

        /**
         * Mengembalikan nama item
         * @return itemName
        */
        string getItemName() const;

        /**
         * Mengembalikan harga item
         * @return itemPrice
        */
        int getItemPrice() const;

        /**
         * Mengembalikan tipe item
         * @return itemType
        */
        ItemType getItemType() const;

        /**
         * Mengubah ID
         * @param newItemID ID baru
        */
        void setItemID(int newItemID);

        /**
         * Mengubah kode unik untuk class Item
         * @param newItemCode Kode unik baru
        */
        void setItemCode(const string& newItemCode);

        /**
         * Mengubah nama item
         * @param newItemName Nama item baru
        */
        void setItemName(const string& newItemName);

        /**
         * Mengubah harga item
         * @param newItemPrice Harga item baru
        */
        void setItemPrice(int newItemPrice);

        /**
         * Mengubah tipe item
         * @param newItemType Tipe item baru
        */
        void setItemType(ItemType newItemType);

        /**
         * Apakah item ini sama dengan item lain
         * @param other item yang ingin dibandingkan
        */
        bool operator==(const Item& other) const;

        /**
         * Menampilkan item
        */
        virtual void displayItem() const = 0;
        
        /**
         * Mengembalikan clone dari item
        */
        virtual Item* cloneItem() const = 0;
};

#endif
