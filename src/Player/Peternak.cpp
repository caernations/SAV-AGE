#include "Peternak.hpp"
#include "../Item/Product.hpp"
#include "../utils/StringProcessor.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <list>

Peternak::Peternak() : Player() {
    kandang = Map<Animal>();
    jumlah_hewan = 0;
    w_kandang = 0;
    h_kandang = 0;
}

Peternak::Peternak(int playerID, const string& playerName, int gulden, int berat_badan, int w_kandang, int h_kandang, int invenSizeW, int invenSizeH) : 
    Player(playerID, playerName, gulden, berat_badan, PETERNAK, invenSizeW, invenSizeH) {
    kandang = Map<Animal>(w_kandang, h_kandang, "Kandang " + playerName);
    jumlah_hewan = 0;
    this->w_kandang = w_kandang;
    this->h_kandang = h_kandang;
}

Peternak::~Peternak() {}

void Peternak::displayGrid() {
    Color color;
    getKandang().printTitle(w_kandang,5);
    getKandang().iterateAlphabet(w_kandang);
    getKandang().print_divider(w_kandang,5);
    for (int i = 0; i < h_kandang; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < w_kandang; j++){
            if (kandang.getMap()[i][j] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " ";
                if(kandang.getMap()[i][j]->isReadyToHarvest())
                    color.colorGreen(kandang.getMap()[i][j]->getItemCode());
                else
                    color.colorRed(kandang.getMap()[i][j]->getItemCode());
                cout << " " << "|";
            }
        }
        cout << endl;
        getKandang().print_divider(w_kandang,5);
    }
}

int Peternak::getJumlahHewan() const {
    return jumlah_hewan;
}

int Peternak::getWKandang() const {
    return w_kandang;
}

int Peternak::getHKandang() const {
    return h_kandang;
}

int Peternak::getMaxHewan() const {
    return w_kandang * h_kandang;
}

void Peternak::setKandang(int kandangX, int kandangY, Animal* item) {
    kandang.set(kandangX, kandangY, item);

    if(kandang.getMap()[kandangY][kandangX] == nullptr){
        if (item != nullptr){
            jumlah_hewan++;
        }
    }
    else if(item == nullptr){
        jumlah_hewan--;
    }
}

Map<Animal>& Peternak::getKandang() {
    return kandang;
}

void Peternak::budidaya() {
    if (!isAnimalInInventory()) throw NoAnimalInInventoryException();
    if (jumlah_hewan >= getMaxHewan()) throw KandangFullException();
    string slot;
    tuple<int, int> pos;
    cout << "Pilih hewan dari penyimpanan" << endl << endl;
    Item& a = takeFromInv(ANIMAL);
    Animal* hewan = dynamic_cast<Animal*>(&a);

    cout << "Pilih petak tanah yang akan ditinggali" << endl << endl;
    displayGrid();
    while(true){
        cout << "Slot: ";
        cin >> slot;
        pos = convertToCoordinate(slot);
        int y = get<0>(pos);
        int x = get<1>(pos);
        if (kandang.getMap()[x][y] != nullptr){
            cout << "Slot sudah terisi" << endl;
        } else if (x < 0 || x >= w_kandang || y < 0 || y >= h_kandang) {
            cout << "Petak kandang tidak valid." << endl;
        } else {
            setKandang(y, x, hewan);
            jumlah_hewan++;
            cout << endl << "Dengan hati-hati, kamu meletakkan seekor " << convertToReadable(std::string(hewan->getItemName()),true,true) << " di kandang." << endl;
            cout << convertToReadable(std::string(hewan->getItemName()), true, true) << " telah menjadi peliharaanmu sekarang!" << endl;
            return;
        }
    }
}

bool Peternak::isFoodTypeCompatible(const std::string& animalType, const std::string& foodType) {
    cout  << endl << "CHECK FOOD COMPATIBLE " << endl << animalType << endl << foodType << endl;
    if (animalType == "Herbivore") {
        return (foodType == "PRODUCT_FRUIT_PLANT");
    } else if (animalType == "Carnivore") {
        return (foodType == "PRODUCT_ANIMAL");
    } else if (animalType == "Omnivore") {
        return true; // Omnivores can eat any type of food
    } else {
        cout << "Unhandled animal type." << endl;
        return false;
    }
}

bool Peternak::isKandangKosong() {
    for (int i = 0; i < h_kandang; i++) {
        for (int j = 0; j < w_kandang; j++) {
            if (kandang.getMap()[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

void Peternak::memberiPangan() {
    if(isKandangKosong()) throw KandangKosongException();
    //cek bisa ngasih makan ato nggak
    auto productlist = getVarianItem(PRODUCT);

    if (productlist.empty()) throw NoFoodForAnimalException();
    bool canfeed = false;
    for (const auto& animal : kandang.convertToList()){
        for (const auto& item : productlist) {
                if (foodForAnimal(animal->getAnimalType(), item.first)) {
                    canfeed = true;
                    break;
                }
            }
        if (canfeed) break;
    }
    if (!canfeed){
        throw NoFoodForAnimalException();
    }

    // Menampilkan peternakan
    cout << "Pilih petak kandang yang akan diberi makan" << endl << endl;
    displayGrid();

    // Memilih petak kandang
    tuple<int, int> pos; 
    while(true) {
        cout << endl;
        cout << "Slot: ";
        string petak;
        cin >> petak;

        pos = convertToCoordinate(petak); 
        int y = get<0>(pos);
        int x = get<1>(pos);

        if (x < 0 || x >= w_kandang || y < 0 || y >= h_kandang) {
            cout << "Petak kandang tidak valid." << endl;
            continue;
        }

        if (kandang.getMap()[x][y] == nullptr) {
            cout << "Tidak ada hewan di petak kandang yang dipilih." << endl;
            continue;
        }

        Animal* a = kandang.getMap()[get<1>(pos)][get<0>(pos)];
        string animalType = a->getAnimalType();

        vector<Item*> inv = getInventory().convertToList();
        bool found = false;

        for (const auto& item : inv) {
            if (foodForAnimal(animalType, item)) {
                found = true;
                break;
            }
        }
        cout << endl;

        if(!found){
            cout << "Tidak ada makanan yang sesuai dengan jenis hewan di petak kandang." << endl;
            continue;
        }
        else {
            cout << "Kamu memilih " << convertToReadable(kandang.getMap()[get<1>(pos)][get<0>(pos)]->getItemName(), true, true) << " untuk diberi makan." << endl;
        }
        break;
    }
    cout << endl;

    while(true) {
        cout << "Pilih pangan yang akan diberikan" << endl << endl;
        Item& p = takeFromInv(PRODUCT);
        Product* foodItem = dynamic_cast<Product*>(&p);

        if (foodForAnimal(kandang.getMap()[get<1>(pos)][get<0>(pos)]->getAnimalType(), foodItem)) {
            cout << kandang.getMap()[get<1>(pos)][get<0>(pos)]->getItemName() << " ingin diberi makan " << convertToReadable(foodItem->getItemName(), true, true) << "." << endl;
            Animal* animal = kandang.getMap()[get<1>(pos)][get<0>(pos)];
            animal->setFed(animal, foodItem->added_weigth, foodItem->convertProductTypeToString(foodItem->getProductType())); 
            cout << endl;
            break;
        } else {
            cout << "Pangan tidak sesuai dengan jenis hewan di petak kandang." << endl << endl;
            // HARUSNYA p DI PUSH LAGI KE INVENTORY
            continue;
        }
    }
}

int Peternak::hitungKekayaan() const {
    vector<Animal*> kandanglist = kandang.convertToList();
    int retval = Player::hitungKekayaan();

    for (Animal*& hewan : kandanglist){
        retval += hewan->getItemPrice();
    }

    return retval;
}

bool Peternak::foodForAnimal(string animalType, Item* food) {
    if (food->getItemType() == PRODUCT) {
        Product* product = dynamic_cast<Product*>(food);
        if (animalType == "CARNIVORE" && product->getProductType() == PRODUCT_ANIMAL) {
            return true;
        } else if (animalType == "HERBIVORE" && product->getProductType() == PRODUCT_FRUIT_PLANT) {
            return true;
        } else if (animalType == "OMNIVORE" && product->getProductType()!= PRODUCT_MATERIAL_PLANT) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void Peternak::panennn(const vector<Product>& products){
    if (isInventoryFull()) throw InventoryFullException();
    string slot;
    tuple<int, int> pos;
    int choiceAnimal;
    int choiceSlot;
    vector<pair<Item*, int>> varians = getVarianItem(ANIMAL);
    vector<pair<Item*, int>> varianReadyToHarvest = getVarianReadyToHarvest();
    pair<Item*,int> chosenAnimal;
    tuple<int, int> posAnimal;
    vector<string> slots;

    displayGrid();
    if(varianReadyToHarvest.empty()) throw NoAnimalToHarvestException();
    cout << endl;
    
    for (pair<Item*, int> item : varians){
        cout <<" - " << item.first->getItemCode() << ": " << convertToReadable(item.first->getItemName(), true, true) << endl;
    }
    cout << endl;

    cout << "Pilih hewan siap panen yang kamu miliki" << endl;
    for (int i = 0; i < varianReadyToHarvest.size(); i++){
        cout<< "    " << i+1 << ". " << varianReadyToHarvest[i].first->getItemCode() << " (" << varianReadyToHarvest[i].second << " petak siap panen)" << endl;
    }

    while (true){
        cout << endl;
        cout << "Nomor hewan yang ingin dipanen: ";
        cin >> choiceAnimal;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid" << endl;
        }
        else if (choiceAnimal < 1 || choiceAnimal > varianReadyToHarvest.size()){
            cout << "Pilihan tidak valid" << endl;
        } else {
            break;
        }
    }

    chosenAnimal = varianReadyToHarvest[choiceAnimal-1];

    vector<Product> animalProducts;
    for(int i = 0; i < products.size(); i++){
        if (products[i].getOrigin() == chosenAnimal.first->getItemName()){
            animalProducts.push_back(products[i]);
        }
    }

    if(animalProducts.empty()){
    cout << "Produk tidak ditemukan" << endl;
    return;
}
    while (true){
        cout << endl;
        cout << "Berapa petak yang ingin dipanen: ";
        cin >> choiceSlot;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid" << endl;
        }
        else if (Player::getItemCountInInventory() + choiceSlot > Player::getMaxItemInInventory()){
            cout << "Jumlah penyimpanan tidak cukup!" << endl;
            return;
        } 
        else if ( choiceSlot < 1 || choiceSlot > chosenAnimal.second){
            cout << "Pilihan tidak valid" << endl;
        }
        else {
            break;
        }
    }

    displayGrid();
    cout << endl;
    cout << "Pilih petak yang ingin dipanen: " << endl;
    for(int i = 0; i < choiceSlot; i++){
        while(true){
            cout << "Petak ke-" << i+1 << ": ";
            cin >> slot;
            pos = convertToCoordinate(slot);
            int x = get<1>(pos);
            int y = get<0>(pos);
            Animal* mapItem = dynamic_cast<Animal*>(kandang.getMap()[x][y]);

            if (x < 0 || x >= w_kandang || y < 0 || y >= h_kandang){
                cout << "Petak tidak valid" << endl;
            } else if (mapItem == nullptr){
                cout << "Petak kosong" << endl;
            } else if (mapItem->getItemCode() != chosenAnimal.first->getItemCode() && !mapItem->isReadyToHarvest()){
                cout << "Hewan tidak sesuai" << endl;
            } else if (mapItem->getItemCode() == chosenAnimal.first->getItemCode() && !mapItem->isReadyToHarvest()){
                cout << "Hewan belum siap dipanen" << endl;
            }
            else {
                kandang.set(x, y, nullptr);
                this->jumlah_hewan--;
                slots.push_back(slot);
                for (const auto& animalProduct : animalProducts) {
                    addToInvEmptySlot(new Product(animalProduct));
                }
                break;
            }
        }
    }

    cout << endl;
    cout << choiceSlot << " petak hewan " << chosenAnimal.first->getItemCode() << " ";
    for(int i = 0; i < slots.size(); i++){
        cout << slots[i];
             cout << ", ";
        }

    cout << "berhasil dipanen" << endl;
}

vector<pair<Item*, int>> Peternak::getVarianReadyToHarvest(){
    vector<pair<Item*, int>> items;
    for (int i = 0; i < h_kandang; i++) {
        for (int j = 0; j < w_kandang; j++) {
            if (kandang.getMap()[i][j] != nullptr && kandang.getMap()[i][j]->getItemType() == ANIMAL && kandang.getMap()[i][j]->isReadyToHarvest()){
                bool found = false;
                for (auto& item : items) {
                    if (item.first->getItemCode() == kandang.getMap()[i][j]->getItemCode() && kandang.getMap()[i][j]->isReadyToHarvest()) {
                        item.second++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    items.push_back(make_pair(kandang.getMap()[i][j], 1));
                }
            }
        }
    }
    return items;
}

bool Peternak::isAnimalInInventory(){
    vector<pair<Item*, int>> items = getVarianItem(ANIMAL);
    return !items.empty();
}