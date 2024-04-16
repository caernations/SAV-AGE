#ifndef STORE_HPP
#define STORE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Item.hpp"
#include "/root/Tubes1_OOP/PetaniPPP/src/Player/Player.hpp"
using namespace std;

enum Action{
    BUY = 1,
    SELL
};

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
    bool canBuy(PlayerType Ptype, ItemType Itype);
    bool canSell(PlayerType Ptype, ItemType Itype);
    void buyAs(Player*& buyer);
    void sellAs(Player*& buyer);
    void openAs(Player*& buyer, Action aksi); // aksi : BUY or SELL

    // setters
    
    void addItem(Item* item,int Quantity);
    void removeItem(int idx,int quantity);
    Item* sellItem(int idx,int Quantity,Player*& buyer);
    
};

#endif // ITEM_HPP
