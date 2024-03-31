#include "Player.hpp"
#include <iostream>


// ctor
Player::Player()
    // : playerType(PETANI), // ini gmn defaultnya yg bener
      playerID(0),
      playerName(""),
      gulden(STARTING_GULDEN),
      beratBadan(STARTING_WEIGHT),
      inventorySizeWidth(10), // atur aja
      inventorySizeHeight(10) {} // atur aja

// ctor with parameter
Player::Player(int playerID, const std::string& playerName, int gulden, int berat_badan, PlayerType playerType)
    : playerType(playerType),
      playerID(playerID),
      playerName(playerName),
      gulden(gulden),
      beratBadan(berat_badan),
      inventorySizeWidth(10), // atur aja
      inventorySizeHeight(10) {} // atur aja

// dtor
Player::~Player() {
    // 
}

int Player::changeGulden(int guldenAmount) {
    gulden += guldenAmount;
    return gulden;
}

void Player::addToInv(Item item, int posX, int posY) {
    int index = posX + posY * inventorySizeWidth;
    inventory[index] = item;
}

Item Player::takeFromInv(int posX, int posY) {
    int index = posX + posY * inventorySizeWidth; 
    Item item = inventory[index];
    inventory.erase(index);
    return item;
}

void Player::consumeFromInv(int posX, int posY) {
}

void Player::consumeItem(Item item) {
}

int Player::getGulden() const {
    return gulden;
}

int Player::getBeratBadan() const {
    return beratBadan;
}

std::string Player::getPlayerName() const {
    return playerName;
}

int Player::getPlayerID() const {
    return playerID;
}

void Player::displayPlayerInfo() const {
    std::cout << "Player ID: " << playerID << ", Name: " << playerName
              << ", Type: " << playerType << ", Gulden: " << gulden
              << ", Weight: " << beratBadan << std::endl;
}

PlayerType Player::getType() const {
    return playerType;
}