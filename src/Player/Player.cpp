#include "Player.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

Player::Player() :
    playerType(WALIKOTA),
    playerID(0),
    playerName(""),
    gulden(STARTING_GULDEN),
    beratBadan(STARTING_WEIGHT),
    invenSizeH(10),
    invenSizeW(10) {
        inventory = Map<Item>(invenSizeW, invenSizeH);
    }

Player::Player(int playerID, const std::string& playerName, int gulden, int berat_badan, PlayerType playerType, int invenSizeW, int invenSizeH) : 
    playerType(playerType),
    playerID(playerID),
    playerName(playerName),
    gulden(gulden),
    beratBadan(berat_badan),
    invenSizeW(invenSizeW),
    invenSizeH(invenSizeH) {
        inventory = Map<Item>(invenSizeW, invenSizeH);
    }

Player::~Player(){}

void Player::changeGulden(int guldenAmount) {
    this->gulden += guldenAmount;
}

void Player::addToInvEmptySlot(Item* item) {
    for (int i = 0; i < invenSizeW; i++) {
        for (int j = 0; j < invenSizeH; j++) {
            if (inventory.getMap()[i][j] == nullptr) {
                inventory.set(i, j, item);
                return;
            }
        }
    } 
}

void Player::addToInv(Item* item, int invenX, int invenY) {
    inventory.set(invenX, invenY, item);
}

Item& Player::takeFromInv(ItemType ItemType) {
    string itemSlot;
    tuple<int, int> slot;
    Player::displayGrid();
    while(true) {
        cout << "Slot: ";
        cin >> itemSlot;
        slot = convertToCoordinate(itemSlot);
        if (inventory.getMap()[get<0>(slot)][get<1>(slot)] == nullptr) {
            cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
        } else if (inventory.getMap()[get<0>(slot)][get<1>(slot)]->getItemType() != ItemType) {
            cout << "Kamu tidak bisa mengambil " << inventory.getMap()[get<0>(slot)][get<1>(slot)]->getItemName() << endl;
        } else {
            inventory.getMap()[get<0>(slot)][get<1>(slot)] = nullptr;
            return *inventory.getMap()[get<0>(slot)][get<1>(slot)];
        }
        cout << "Silahkan masukan slot yang berisi " << ItemType << endl;
        cout << endl;
    }
}

void Player::consumeFromInv() {
    // if (inventory.isEmpty()) throw InventoryEmptyException();
    int posX, posY;
    while (true) {
        cin >> posX >> posY;
        if (inventory.getMap()[posX][posY] == nullptr) {
            cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
        } else if (Product* product = dynamic_cast<Product*>(inventory.getMap()[posX][posY])) {
            if (product->isProductConsumable()) {
                beratBadan += product->added_weigth;
                inventory.getMap()[posX][posY] = nullptr;
                delete product;
                return;
            } else {
                cout << "Apa yang kamu lakukan??\\!! Kamu mencoba untuk memakan itu?\\!!" << "\n";
            }
        } else {
            cout << "Kamu tidak bisa memakan " << inventory.getMap()[posX][posY]->getItemName() << "\n";
        }
        cout << "Silahkan masukan slot yang berisi makanan." << "\n";
    }
}

void Player::displayGrid() {
    getInventory().iterateAlphabet(invenSizeW);
    getInventory().print_divider(invenSizeW,5);
    for (int i = 0; i <invenSizeH; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < invenSizeW; j++){
            if (getInventory().getMap()[j][i] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " " << getInventory().getMap()[j][i]->getItemCode() << " " << "|";
            }
        }
        cout << "\n";
        getInventory().print_divider(invenSizeW,5);

    }
}

vector<pair<Item*, int>> Player::getVarianItem() {
    vector<pair<Item*, int>> items;
    for (int i = 0; i < invenSizeW; i++) {
        for (int j = 0; j < invenSizeH; j++) {
            if (inventory.getMap()[i][j] != nullptr) {
                bool found = false;
                for (auto& item : items) {
                    if (item.first->getItemCode() == inventory.getMap()[i][j]->getItemCode()) {
                        item.second++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    items.push_back(make_pair(inventory.getMap()[i][j], 1));
                }
            }
        }
    }
    return items;
}

Map<Item>& Player::getInventory() {
    return inventory;
}

int Player::getGulden() const {
    return gulden;
}

int Player::getBeratBadan() const {
    return beratBadan;
}

string Player::getPlayerName() const {
    return playerName;
}

int Player::getPlayerID() const {
    return playerID;
}

void Player::displayPlayerInfo() const {
    cout << "Player ID: " << playerID << ", Name: " << playerName
              << ", Type: " << playerType << ", Gulden: " << gulden
              << ", Weight: " << beratBadan << endl;
}

PlayerType Player::getType() const {
    return playerType;
}

int Player::getInvenW() {
    return invenSizeW;
}

int Player::getInvenH() {
    return invenSizeH;
}

bool Player::isInventoryFull() {
    for (int i = 0; i < invenSizeW; i++) {
        for (int j = 0; j < invenSizeH; j++) {
            if (inventory.getMap()[i][j] == nullptr) {
                return false;
            }
        }
    }
    return true;
}