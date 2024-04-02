#ifndef STORE_HPP
#define STORE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Item.hpp"
using namespace std;


class Store{
private:
    vector<Item*> items; // <item1,item2,item3,...>
    vector<int> Quantity; //<quantity of item1,quantity of item2,quantity of item3,...>

public:
    Store();
    Store(vector<Item*> ItemList,vector<int>& quantity);
    ~Store(); // dtor

    // getters
    
    int getItemQuantity(const Item* item) const;

    // Mengembalikan index dari item bila ada
    // Mengembalikan -1 bila tidak ada
    int isinStore(const Item* item) const;

    int totalprice(int idx,int quantity);
    void displayStore();

    // setters
    
    void addItem(Item* item,int Quantity);
    void removeItem(int idx,int quantity);
    Item* sellItem(int idx,int Quantity,int money);
    
};

#endif // ITEM_HPP
