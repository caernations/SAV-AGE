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
            if (lahan.getMap()[j][i] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " ";
                if(lahan.getMap()[j][i]->isReadyToHarvest())
                    color.colorGreen(lahan.getMap()[j][i]->getItemCode());
                else
                    color.colorRed(lahan.getMap()[j][i]->getItemCode());
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
}

Map<Plant>& Petani::getLahan() {
    return lahan;
}

void Petani::budidaya(){
    // if (isInventoryFull()) throw InventoryFullException();
    // if (jumlah_tumbuhan >= getMaxTumbuhan()) throw LahanFullException();
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
    while(true){
        cout << "Slot: ";
        cin >> slot;
        pos = convertToCoordinate(slot);
        if (lahan.getMap()[get<0>(pos)][get<1>(pos)] != nullptr){
            cout << "Slot sudah terisi" << endl;
        } else {
            lahan.set(get<0>(pos), get<1>(pos), plant);
            jumlah_tumbuhan++;
            cout << "Cangkul, cangkul, cangkul yang dalam~!" << endl;
            cout << convertToReadable(plant->getItemName(), false, false) << " berhasil ditanami" << endl;
            return;
        }
    }

}

void Petani::panennn(vector<Product*>& products){
    // if (isInventoryFull()) throw InventoryFullException();
    string slot;
    tuple<int, int> pos;
    int choicePlant;
    int choiceSlot;
    vector<pair<Item*, int>> varians = getVarianItem(PLANT);
    vector<pair<Item*, int>> varianReadyToHarvest = getVarianReadyToHarvest();
    pair<Item*,int> chosenPlant;
    tuple<int, int> posPlant;
    vector<string> slots;
    Product* plantProduct = new Product();

    displayGrid();
    // if(varianReadyToHarvest.empty()) throw NoItemToHarvestException();
    if (varianReadyToHarvest.empty()){
        cout << "Tidak ada tanaman yang siap dipanen" << endl;
        cout << endl;
        return;
    }
    cout << endl;
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
        if (products[i]->getOrigin() == chosenPlant.first->getItemName()){
            plantProduct = new Product(*products[i]);
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
            int x = get<0>(pos);
            int y = get<1>(pos);
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
                lahan.set(x, y, nullptr);
                jumlah_tumbuhan--;
                slots.push_back(slot);
                addToInvEmptySlot(plantProduct);
                break;
            }
        }
    }

    cout << endl;
    cout << choiceSlot << " petak tananam " << chosenPlant.first->getItemCode() << " ";
    for(int i = 0; i < slots.size(); i++){
        cout << slots[i];
             cout << ", ";
        }

    cout << "berhasil dipanen" << endl;
}

vector<pair<Item*, int>> Petani::getVarianReadyToHarvest(){
    vector<pair<Item*, int>> items;
    for (int i = 0; i < w_lahan; i++) {
        for (int j = 0; j < h_lahan; j++) {
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
