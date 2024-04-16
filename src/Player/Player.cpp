#include "Player.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

Player::Player() :
    playerType(WALIKOTA),
    playerID(0),
    playerName(""),
    gulden(STARTING_GULDEN),
    beratBadan(STARTING_WEIGHT),
    invenSizeH(10),
    invenSizeW(10),
    itemCountInInventory(0)
    {
        inventory = Map<Item>(invenSizeW, invenSizeH, "Penyimpanan");
        maxItemInInventory = invenSizeW * invenSizeH;
    }

Player::Player(int playerID, const std::string& playerName, int gulden, int berat_badan, PlayerType playerType, int invenSizeW, int invenSizeH) : 
    playerType(playerType),
    playerID(playerID),
    playerName(playerName),
    gulden(gulden),
    beratBadan(berat_badan),
    invenSizeW(invenSizeW),
    invenSizeH(invenSizeH),
    itemCountInInventory(0) {
        inventory = Map<Item>(invenSizeW, invenSizeH, "Penyimpanan");
        maxItemInInventory = invenSizeW * invenSizeH;
    }

Player::~Player(){}

void Player::changeGulden(int guldenAmount) {
    this->gulden += guldenAmount;
}

void Player::addToInvEmptySlot(Item* item) {
    for (int i = 0; i < invenSizeH; i++) {
        for (int j = 0; j < invenSizeW; j++) {
            if (inventory.getMap()[i][j] == nullptr) {
                inventory.set(j, i, item);
                itemCountInInventory++;
                return;
            }
        }
    } 
}

void Player::addToInvSpecific(Item* item) {
    string slot;
    while(true) {
        cout << "Slot: ";
        cin >> slot;
        tuple<int, int> slots = convertToCoordinate(slot);
        int y = get<0>(slots);
        int x = get<1>(slots);
        if (inventory.getMap()[x][y] == nullptr) {
            inventory.set(x, y, item);
            itemCountInInventory++;
            return;
        } else {
            cout << "Slot sudah terisi. Silakan masukkan slot yang kosong." << endl;
        }
    }

}

void Player::addToInv(Item* item) {
    int option;
    cout << "Pilihan penambahan item ke penyimpanan: " << endl;
    cout << "1. Tambahkan ke slot kosong" << endl;
    cout << "2. Pilih slot" << endl;
    while (true)
    {
        cout << "Pilihan angka: ";
        cin >> option;
        cout << endl;
        if (cin.fail() || option < 1 || option > 2)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Silakan masukkan angka 1 atau 2: " << endl;
        }
        else
        {
            break;
        }
    }
    
    if (option == 1) {
        addToInvEmptySlot(item);
    } else {
        addToInvSpecific(item);
    }
}

Item& Player::takeFromInv(ItemType ItemType) {
    string itemSlot;
    tuple<int, int> slot;
    Player::displayGrid();
    cout << endl;
    while(true) {
        cout << "Slot: ";
        cin >> itemSlot;
        cout << endl;
        slot = convertToCoordinate(itemSlot);
        int y = get<0>(slot);
        int x = get<1>(slot);
        
        if (cin.fail() || x < 0 || x >= invenSizeW || y < 0 || y >= invenSizeH) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid slot." << endl;
            continue; 
        }

        if (inventory.getMap()[x][y] == nullptr) {
            cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
        } else if (inventory.getMap()[x][y]->getItemType() != ItemType) {
            cout << "Kamu tidak bisa mengambil " << inventory.getMap()[x][y]->getItemName() << endl;
        } else {
            Item& item = *inventory.getMap()[x][y];
            inventory.set(x, y, nullptr);
            itemCountInInventory--;
            return item;
        }
        cout << "Silahkan masukan slot yang berisi " << itemTypeToString(ItemType) << "." << endl;
        cout << endl;
    }
}

void Player::consumeFromInv() {
    if (isInventoryEmpty()) throw InventoryEmptyException();
    if (!isThereFood()) throw NoFoodInInventoryException();
    string slot;
    tuple<int,int> slots;
    cout <<"Pilih makanan dari penyimpanan"<<endl << endl;
    Player::displayGrid();
    Product* product;
    while (true) {
        cout << "Slot: ";
        cin >> slot;
        slots = convertToCoordinate(slot);
        int y = get<0>(slots);
        int x = get<1>(slots);
        cout << endl << endl;
        if (inventory.getMap()[x][y] == nullptr) {
            cout << "Kamu mengambil harapan kosong dari penyimpanan." << endl;
        } else if (product = dynamic_cast<Product*>(inventory.getMap()[x][y])) {
            if (product->isProductConsumable()) {
                addWeight(product->added_weigth);
                cout << "Dengan lahapnya, kamu memakanan hidangan itu" << endl;
                cout << "Alhasil, berat badan kamu naik menjadi " << beratBadan << endl;
                inventory.getMap()[x][y] = nullptr;
                itemCountInInventory--;
                return;
            } else {
                cout << "Apa yang kamu lakukan??\\!! Kamu mencoba untuk memakan itu?\\!!" << "\n";
            }
        } else {
            cout << "Kamu tidak bisa memakan " << inventory.getMap()[x][y]->getItemName() << "\n";
        }
        cout << "Silahkan masukan slot yang berisi makanan." << "\n";
    }
    

}

void Player::displayGrid() {
    getInventory().printTitle(invenSizeW, 5);
    getInventory().iterateAlphabet(invenSizeW);
    getInventory().print_divider(invenSizeW,5);
    for (int i = 0; i <invenSizeW; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < invenSizeH; j++){
            if (getInventory().getMap()[i][j] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " " << getInventory().getMap()[i][j]->getItemCode() << " " << "|";
            }
        }
        cout << "\n";
        getInventory().print_divider(invenSizeW,5);
    }
}


void Player::addWeight(int addedWeight){
    this->beratBadan+=addedWeight;
}

void Player::displayPlayerInfo() const {
    cout << "Player ID: " << playerID << ", Name: " << playerName
              << ", Type: " << playerType << ", Gulden: " << gulden
              << ", Weight: " << beratBadan << endl;
}

vector<pair<Item*, int>> Player::getVarianItem(ItemType ItemType) {
    vector<pair<Item*, int>> items;
    for (int i = 0; i < invenSizeW; i++) {
        for (int j = 0; j < invenSizeH; j++) {
            if (inventory.getMap()[i][j] != nullptr && inventory.getMap()[i][j]->getItemType() == ItemType){
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

string Player::getPlayerName() const {
    return playerName;
}

PlayerType Player::getType() const {
    return playerType;
}

string Player::playerTypeToString() const {
    if (playerType == WALIKOTA) {
        return "Walikota";
    } else if (playerType == PETANI) {
        return "Petani";
    } else if (playerType == PETERNAK) {
        return "Peternak";
    } else {
        return "UNKNOWN";
    }
}

int Player::getPlayerID() const {
    return playerID;
}

int Player::getGulden() const {
    return gulden;
}

int Player::getBeratBadan() const {
    return beratBadan;
}

int Player::getInvenW() {
    return invenSizeW;
}

int Player::getInvenH() {
    return invenSizeH;
}

int Player::getMaxItemInInventory() const {
    return maxItemInInventory;
}

int Player::getItemCountInInventory() const {
    return this->itemCountInInventory;
}

int Player::hitungKekayaan() const{
    int retval = 0;
    vector<Item*> items = inventory.convertToList();
    for (Item*& item : items){
        retval += item->getItemPrice();
    }
    return retval;
}

bool Player::isInventoryFull() {
    return itemCountInInventory == maxItemInInventory;
}

bool Player::isInventoryEmpty() {
    return itemCountInInventory == 0;
}

bool Player::isThereFood() {
    int foodCount = 0;
    vector<Item*> items = inventory.convertToList();
    for (Item*& item : items) {
        if (dynamic_cast<Product*>(item) != nullptr) {
            if(dynamic_cast<Product*>(item)->isProductConsumable()) {
                foodCount++;
            }
        }
    }
    return foodCount > 0;
}

void Player::updateItemCount()
{
    int retval = 0;

    for (vector<Item*> x : inventory.getMap()){
        for (Item* item : x){
            if (item != nullptr){
                retval++;
            }
        }
    }

    itemCountInInventory = retval;
}

string Player::itemTypeToString(ItemType type) {
    static const char* itemTypeStrings[] = {
        "building",
        "plant",
        "animal",
        "product",
        "recipe" 
    };

    // Check if the type is within range
    if (type >= 0 && type < NUM_ITEM_TYPES) {
        return itemTypeStrings[type];
    } else {
        return "UNKNOWN";
    }
}

void Player::budidaya() {
    cout << "Player melakukan budidaya" << endl;
}

void Player::panennn(const vector<Product>& products) {
    cout << "Player melakukan panen" << endl;
}

void Player::removeFromInv(const string& itemName, int amount) {
    if (amount == 0) return;
    for (int i = 0; i < invenSizeH; i++) {
        for (int j = 0; j < invenSizeW; j++) {
            Item* item = inventory.getMap()[i][j];
            if (item != nullptr && item->getItemName() == itemName){
                inventory.set(j, i, nullptr);
                itemCountInInventory--;
                removeFromInv(itemName, amount - 1);
            }
        }
    }
}

