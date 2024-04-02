#include "Petani.hpp"
#include <iostream>
#include <iomanip>

Petani::Petani() : Player() {
    lahan = Map<Plant>();
    jumlah_tumbuhan = 0;
    w_lahan = 0;
    h_lahan = 0;
}

Petani::Petani(int playerID, const string& playerName, int gulden, int berat_badan, int w_lahan, int h_lahan, int invenSizeW, int invenSizeH) : 
    Player(playerID, playerName, gulden, berat_badan, PETANI, invenSizeW, invenSizeH) {
    lahan = Map<Plant>(w_lahan, h_lahan);
    jumlah_tumbuhan = 0;
    this->w_lahan = w_lahan;
    this->h_lahan = h_lahan;
}

Petani::~Petani(){}

void Petani::displayGrid(){
    Color color;
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
    Item& p = takeFromInv(PLANT);
    Plant* plant = dynamic_cast<Plant*>(&p);

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
            cout << convertToReadable(plant->getItemName()) << " berhasil ditanami" << endl;
            return;
        }


    }

}