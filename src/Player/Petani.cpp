#include "Petani.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

Petani::Petani() : Player() {
    lahan = Map<Plant>();
    jumlah_tumbuhan = 0;
    w_lahan = 0;
    h_lahan = 0;
}

Petani::Petani(int playerID, const string& playerName, int gulden, int berat_badan, int w_lahan, int h_lahan, int invenSizeW, int invenSizeH) : 
    Player(playerID, playerName, gulden, berat_badan, PETANI, invenSizeW, invenSizeH) {
    lahan = Map<Plant>(w_lahan, h_lahan, "Lahan " + playerName);
    jumlah_tumbuhan = 0;
    this->w_lahan = w_lahan;
    this->h_lahan = h_lahan;
}

Petani::~Petani(){}

void Petani::displayGrid(){
    Color color;
    getLahan().printTitle(w_lahan,5);
    getLahan().iterateAlphabet(w_lahan);
    getLahan().print_divider(w_lahan,5);
    for (int i = 0; i < h_lahan; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < w_lahan; j++){
            if (lahan.getMap()[i][j] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " ";
                if(lahan.getMap()[i][j]->isReadyToHarvest())
                    color.colorGreen(lahan.getMap()[i][j]->getItemCode());
                else
                    color.colorRed(lahan.getMap()[i][j]->getItemCode());
                cout << " " << "|";
            }
        }
        cout << endl;
        getLahan().print_divider(w_lahan,5);
    }
}

int Petani::getJumlahTumbuhan() const {
    return jumlah_tumbuhan;
}

int Petani::getWLahan() const {
    return w_lahan;
}

int Petani::getHLahan() const {
    return h_lahan;
}

int Petani::getMaxTumbuhan() const {
    return w_lahan * h_lahan;
}

void Petani::setLahan(int x, int y, Plant* item){
    lahan.set(x, y, item);
    
    if(lahan.getMap()[x][y] == nullptr){
        if (item != nullptr){
            jumlah_tumbuhan++;
        }
    }
    else if(item == nullptr){
        jumlah_tumbuhan--;
    }
}

Map<Plant>& Petani::getLahan() {
    return lahan;
}

void Petani::budidaya(){
    if (!isPlantInInventory()) throw NoPlantInInventoryException();
    if (jumlah_tumbuhan >= getMaxTumbuhan()) throw LahanFullException();
    string slot;
    tuple<int, int> pos;
    cout << "Pilih tanaman dari penyimpanan:" << endl;
    cout << endl;   
    Item& p = takeFromInv(PLANT);
    Plant* plant = dynamic_cast<Plant*>(&p);

    cout << "Kamu memilih " << convertToReadable(plant->getItemName(), true, true) <<"."<<endl;
    cout << endl;
    cout << "Pilih petak tanah yang akan ditanami" << endl << endl;

    displayGrid(); 
    cout << endl;
    while(true){
        cout << "Slot: ";
        cin >> slot;
        pos = convertToCoordinate(slot);
        int y = get<0>(pos);
        int x = get<1>(pos);
        if (x == -1 || y == -1) {
            cout << "Slot tidak valid. Silakan masukkan slot yang valid." << endl;
            continue;
        }
        if (lahan.getMap()[x][y] != nullptr){
            cout << "Slot sudah terisi" << endl;
        } else {
            setLahan(y, x, plant);
            cout << "Cangkul, cangkul, cangkul yang dalam~!" << endl;
            cout << convertToReadable(plant->getItemName(), false, false) << " berhasil ditanami" << endl;
            return;
        }
    }
}

void Petani::panennn(const vector<Product>& products){
    if (isInventoryFull()) throw InventoryFullException();
    string slot;
    tuple<int, int> pos;
    int choicePlant;
    int choiceSlot;
    vector<pair<Item*, int>> varians = getVarianItem(PLANT);
    cout << "Getting harvest list..." << endl;
    vector<pair<Item*, int>> varianReadyToHarvest = getVarianReadyToHarvest();
    pair<Item*,int> chosenPlant;
    tuple<int, int> posPlant;
    vector<string> slots;
    Product* plantProduct = new Product();

    displayGrid();
    if(varianReadyToHarvest.empty()) throw NoPlantToHarvestException();

    for (pair<Item*, int> item : varians){
        cout <<" - " << item.first->getItemCode() << ": " << convertToReadable(item.first->getItemName(), true, true) << endl;
    }
    cout << endl;

    cout << "Pilih tanaman siap panen yang kamu miliki" << endl;
    for (int i = 0; i < varianReadyToHarvest.size(); i++){
        cout<< "    " << i+1 << ". " << varianReadyToHarvest[i].first->getItemCode() << " (" << varianReadyToHarvest[i].second << " petak siap panen)" << endl;
    }

    while (true){
        cout << endl;
        cout << "Nomor tanaman yang ingin dipanen: ";
        cin >> choicePlant;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid" << endl;
        }
        else if (choicePlant < 1 || choicePlant > varianReadyToHarvest.size()){
            cout << "Pilihan tidak valid" << endl;
        } else {
            break;
        }
    }

    chosenPlant = varianReadyToHarvest[choicePlant-1];

    for(int i = 0; i < products.size(); i++){
        if (products[i].getOrigin() == chosenPlant.first->getItemName()){
            plantProduct = new Product(products[i]);
            break;
        }
    }

    if(plantProduct->getItemCode() == ""){
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
        else if ( choiceSlot < 1 || choiceSlot > chosenPlant.second){
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
            int y = get<0>(pos);
            int x = get<1>(pos);
            Plant* mapItem = dynamic_cast<Plant*>(lahan.getMap()[x][y]);

            if (x < 0 || x >= w_lahan || y < 0 || y >= h_lahan){
                cout << "Petak tidak valid" << endl;
            } else if (mapItem == nullptr){
                cout << "Petak kosong" << endl;
            } else if (mapItem->getItemCode() != chosenPlant.first->getItemCode() && !mapItem->isReadyToHarvest()){
                cout << "Tanaman tidak sesuai" << endl;
            } else if (mapItem->getItemCode() == chosenPlant.first->getItemCode() && !mapItem->isReadyToHarvest()){
                cout << "Tanaman belum siap dipanen" << endl;
            }
            else {
                setLahan(x, y, nullptr);
                slots.push_back(slot);
                cout << endl;
                addToInv(plantProduct);
                break;
            }
        }
    }

    cout << choiceSlot << " petak tananam " << chosenPlant.first->getItemCode() << " ";
    for(int i = 0; i < slots.size(); i++){
        cout << slots[i];
             cout << ", ";
        }

    cout << "berhasil dipanen" << endl;
}

vector<pair<Item*, int>> Petani::getVarianReadyToHarvest(){
    vector<pair<Item*, int>> items;
    for (int i = 0; i < h_lahan; i++) {
        for (int j = 0; j < w_lahan; j++) {
            if (lahan.getMap()[i][j] != nullptr && lahan.getMap()[i][j]->getItemType() == PLANT && lahan.getMap()[i][j]->isReadyToHarvest()){
                bool found = false;
                for (auto& item : items) {
                    if (item.first->getItemCode() == lahan.getMap()[i][j]->getItemCode() && lahan.getMap()[i][j]->isReadyToHarvest()) {
                        item.second++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    items.push_back(make_pair(lahan.getMap()[i][j], 1));
                }
            }
        }
    }
    return items;
}

int Petani::hitungKekayaan() const{

    vector<Plant*> lahanlist = lahan.convertToList();
    int retval = Player::hitungKekayaan();

    for (Plant*& tanaman : lahanlist){
        retval += tanaman->getItemPrice();
    }

    return retval;
}

bool Petani::isPlantInInventory(){
    vector<pair<Item*, int>> items = getVarianItem(PLANT);
    return !items.empty();
}