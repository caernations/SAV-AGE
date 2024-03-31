#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <string>
#include <vector>
#include <utility>
#include "../Item/Item.hpp"


enum PlayerType {
    PETANI,
    PETERNAK,
    WALIKOTA
};

class Player {
private:
    const int STARTING_WEIGHT = 40;
    const int STARTING_GULDEN = 50;

    PlayerType playerType;
    int playerID;
    std::string playerName;
    int gulden;
    int beratBadan;
    std::map<int, Item> inventory; 

    int inventorySizeWidth;
    int inventorySizeHeight;

public:
    Player();

    Player(int playerID, const std::string& playerName, int gulden, int berat_badan, PlayerType playerType);

    virtual ~Player();

    int changeGulden(int guldenAmount);

    void addToInv(Item item, int posX, int posY);

    Item takeFromInv(int posX, int posY);

    void consumeFromInv(int posX, int posY);
    
    void consumeItem(Item item);

    // virtual void playerAction() = 0; // pure virtual

    virtual void playerAction() {
        std::cout << playerName << " melakukan aksi default." << std::endl;
    }

    // getter
    int getGulden() const;
    int getBeratBadan() const;
    std::string getPlayerName() const;
    int getPlayerID() const;
    void displayPlayerInfo() const;
    PlayerType getType() const;
};

#endif 