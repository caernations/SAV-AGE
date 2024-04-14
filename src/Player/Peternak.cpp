#include "Peternak.hpp"
#include "../Item/Product.hpp"
#include "../utils/StringProcessor.hpp"
#include <iostream>
#include <iomanip>

Peternak::Peternak() : Player() {
    inventory = Map<Item>();
    kandang = Map<Animal>();
    jumlah_hewan = 0;
    w_kandang = 0;
    h_kandang = 0;
}

Peternak::Peternak(int playerID, const string& playerName, int gulden, int berat_badan, int w_kandang, int h_kandang, int invenSizeW, int invenSizeH) : 
    Player(playerID, playerName, gulden, berat_badan, PETERNAK, invenSizeW, invenSizeH) {
    inventory = Map<Item>(this->getInvenW(), this->getInvenH());
    kandang = Map<Animal>(w_kandang, h_kandang, "Kandang " + playerName);
    jumlah_hewan = 0;
    this->w_kandang = w_kandang;
    this->h_kandang = h_kandang;
}

Peternak::~Peternak() {}

void Peternak::displayGrid() {
    cout << "================[ Peternakan ]===================" << endl;
    Color color;
    getKandang().iterateAlphabet(w_kandang);
    getKandang().print_divider(w_kandang,5);
    for (int i = 0; i < h_kandang; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < w_kandang; j++){
            if (kandang.getMap()[j][i] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " ";
                if(kandang.getMap()[j][i]->isReadyToHarvest())
                    color.colorGreen(kandang.getMap()[j][i]->getItemCode());
                else
                    color.colorRed(kandang.getMap()[j][i]->getItemCode());
                cout << " " << "|";
            }
        }
        cout << endl;
        getKandang().print_divider(w_kandang,5);
    }
}

void Peternak::displayInventory() {
    int w_inventory = this->getInvenW();
    int h_inventory = this->getInvenH();
    inventory.iterateAlphabet(w_inventory);
    inventory.print_divider(w_inventory,5);
    for (int i = 0; i < h_inventory; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < w_inventory; j++) {
            if (inventory.getMap()[j][i] == nullptr) {
                cout << "     " << "|";
            } else {
                cout << " ";
                cout << inventory.getMap()[j][i]->getItemCode();
                cout << " " << "|";
            }
        }
        cout << endl;
        inventory.print_divider(w_inventory,5);
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
}

Map<Animal>& Peternak::getKandang() {
    return kandang;
}

void Peternak::budidaya() {
    cout << "Pilih hewan dari penyimpanan" << endl;
    string slot;
    tuple<int, int> pos;
    Item& a = takeFromInv(ANIMAL);
    Animal* hewan = dynamic_cast<Animal*>(&a);

    cout << "Pilih petak tanah yang akan ditinggali" << endl;
    displayGrid();
    while(true){
        cout << "Slot: ";
        cin >> slot;
        pos = convertToCoordinate(slot);
        if (kandang.getMap()[get<0>(pos)][get<1>(pos)] != nullptr){
            cout << "Slot sudah terisi" << endl;
        } else {
            kandang.set(get<0>(pos), get<1>(pos), hewan);
            jumlah_hewan++;
            cout << "Dengan hati-hati, kamu meletakkan seekor " << convertToReadable(std::string(hewan->getItemName()),true,true) << " di kandang." << endl;
            cout << convertToReadable(std::string(hewan->getItemName()), true, true) << " telah menjadi peliharaanmu sekarang!" << endl;
            break;
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

void Peternak::memberiPangan() {
    // if(kandang.isEmpty()) throw KandangKosongException();
    // vector<pair<Item*, int>> varians = getVarianItem(ANIMAL);

    // Menampilkan peternakan
    displayGrid();

    // Memilih petak kandang
    tuple<int, int> pos; // Declaring pos here
    while(true) {
        cout << endl;
        cout << "Pilih petak kandang yang akan diberi makan: ";
        string petak;
        cin >> petak;

        pos = convertToCoordinate(petak); // Assigning pos here
        int x = get<0>(pos);
        int y = get<1>(pos);

        if (x < 0 || x >= w_kandang || y < 0 || y >= h_kandang) {
            cout << "Petak kandang tidak valid." << endl;
            continue;
        }

        if (kandang.getMap()[get<0>(pos)][get<1>(pos)] == nullptr) {
            cout << "Tidak ada hewan di petak kandang yang dipilih." << endl;
            continue;
        }

        string animalType = kandang.getMap()[get<0>(pos)][get<1>(pos)]->getAnimalType();
        vector<pair<Item*, int>> varianReadyToFeed = getVarianReadyToFeed(animalType);

        if(varianReadyToFeed.empty()){
            cout << "Tidak ada makanan yang sesuai dengan jenis hewan di petak kandang." << endl;
            continue;
        }
        else {
            cout << endl << "Kamu memilih " << convertToReadable(kandang.getMap()[get<0>(pos)][get<1>(pos)]->getItemName(), true, true) << " untuk diberi makan." << endl;
        }

        break;
    }

    cout << endl;

    // Menampilkan penyimpanan
    cout << endl << "================[ Penyimpanan ]=================" << endl;
    displayInventory();

    // Memilih slot penyimpanan untuk pangan
    cout << "Pilih pangan yang akan diberikan:";
    string slot;
    cin >> slot;

    // Mengonversi input slot menjadi koordinat
    tuple<int, int> storagePos = convertToCoordinate(slot);
    int storageX = get<0>(storagePos);
    int storageY = get<1>(storagePos);

    // Periksa apakah slot penyimpanan valid
    int w_inventory = this->getInvenW(); // Declaring w_inventory here
    int h_inventory = this->getInvenH(); // Declaring h_inventory here
    if (storageX < 0 || storageX >= w_inventory || storageY < 0 || storageY >= h_inventory) {
        cout << "Slot penyimpanan tidak valid." << endl;
        return;
    }

    // Periksa apakah slot kosong
    if (inventory.getMap()[storageX][storageY] == nullptr) {
        cout << "Slot penyimpanan masih kosong." << endl;
        return;
    }

    // Memberikan makanan kepada hewan
    Product* foodItem = dynamic_cast<Product*>(inventory.getMap()[storageX][storageY]);
    Animal* animal = kandang.getMap()[get<0>(pos)][get<1>(pos)]; // Using pos instead of x and y
    animal->setFed(foodItem->added_weigth, foodItem->convertProductTypeToString(foodItem->getProductType())); 
    inventory.set(storageX, storageY, nullptr);
    delete foodItem;

    // Menampilkan informasi bahwa hewan sudah diberi makan
    cout << "Hewan telah diberi makan." << endl;
}

int Peternak::hitungKekayaan() const {
    return this->getGulden();
}

vector<pair<Item*, int>> Peternak::getVarianReadyToFeed(const std::string& animalType) {
    cout << "MASUKKKKKKK" << endl;
    vector<pair<Item*, int>> items;
    int w_inventory = this->getInvenW();
    int h_inventory = this->getInvenH();
    for (int i = 0; i < h_inventory; i++) {
        for (int j = 0; j < w_inventory; j++) {
            if (inventory.getMap()[i][j] != nullptr && inventory.getMap()[i][j]->getItemType() == PRODUCT) {
                cout << "OKKKKKKKKKKK" << endl;
                bool found = false;
                for (auto& item : items) {
                    Product* product = dynamic_cast<Product*>(item.first); 
                    if (isFoodTypeCompatible(animalType, product->convertProductTypeToString(product->getProductType()))) {
                        cout << endl << "COMPATIBILITY CHECK" << endl << animalType << endl << product->convertProductTypeToString(product->getProductType()) << endl;
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    return items;
}

