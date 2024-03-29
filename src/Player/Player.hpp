#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include "../Item/Item.hpp"

class Player {
private:
    const int STARTING_WEIGHT = 40;
    const int STARTING_GULDEN = 50;

    int inventorySizeWidth;
    int inventorySizeHeight;

    int gulden;
    int beratBadan;
    std::map<int, Item> inventory; 

public:
    // Create player with default values and an empty inventory
    Player();

    // Create player with gulden, berat_badan, and inventory
    Player(int gulden, int berat_badan);

    // dtor
    ~Player();

    int changeGulden(int amt);

    void addToInv(Item item, int posX, int posY);

    Item takeFromInv(int posX, int posY);

    void consumeFromInv(int posX, int posY);
    
    void consumeItem(Item item);
};

#endif 