#include "Petani.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

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

Petani::~Petani() {}

void Petani::displayLahan(){
    getLahan().iterateAlphabet(w_lahan);
    getLahan().print_divider(w_lahan,5);
    for (int i = 0; i < h_lahan; i++){
        cout << setw(2) << setfill('0') << i+1 << " ";
        cout << "|";
        for (int j = 0; j < w_lahan; j++){
            if (lahan.getMap()[j][i] == nullptr){
                cout << "     " << "|";
            } else {
                cout << " " << lahan.getMap()[j][i]->getItemCode() << " " << "|";
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

