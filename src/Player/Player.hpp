#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include "../Item/Item.hpp"

class Player {
private:
    int gulden;
    int berat_badan;
    std::map<int, Item> inventory; 

public:
    Player(); // ctor
    int changeGulden(int amt);
    void addToInv(Item item, int posX, int posY);
    Item takeFromInv(int posX, int posY);
    void consumeFromInv(int posX, int posY);
    void consumeItem(Item item);
};

#endif 