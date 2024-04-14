#include "Peternak.hpp"
#include <iostream>
#include <vector>

// g++ -o driverPeternak driverPeternak.cpp Peternak.cpp ../Item/Item.cpp ../Item/Animal.cpp ../Item/Product.cpp ../utils/StringProcessor.cpp ../utils/Color.cpp Player.cpp

using namespace std;

int main() {
    vector<vector<Item*>> inven;
    inven.resize(5);

    for(int i = 0; i < 5; i++){
        inven[i].resize(5,nullptr);
    }

    Peternak p(1, "Dani", 100, 50, 5, 5, 10, 10);
    cout << "Jumlah hewan: " << p.getJumlahHewan() << endl;
    cout << "Lebar kandang: " << p.getWKandang() << endl;
    cout << "Tinggi kandang: " << p.getHKandang() << endl;
    cout << "Maksimum hewan yang bisa diternak: " << p.getMaxHewan() << endl;
    cout << "Jumlah kekayaan: " << p.hitungKekayaan() << endl;

    Animal* hewan1 = new Animal(1, "COW", 10, "COW", "HERBIVORE", 6);
    Animal hewan2(2, "SHP", 15, "SHP", "HERBIVORE", 10);
    Animal hewan3(3, "SNK", 13, "SNK", "CARNIVORE", 4);
    Animal hewan4(4, "CHK", 12, "CHK", "OMNIVORE", 3);
    Animal hewan5(5, "RBT", 10, "RBT", "HERBIVORE", 4);

    p.setKandang(3, 2, hewan1);
    p.addToInvEmptySlot(&hewan2);
    p.addToInvEmptySlot(&hewan3);
    p.addToInvEmptySlot(&hewan4);
    p.addToInvEmptySlot(&hewan5);

    p.getInventory().set(3, 5, hewan1);
    p.setKandang(0, 0, &hewan3);
    p.setKandang(0, 1, &hewan4);

    p.budidaya();

    cout << "Setelah budidaya, jumlah hewan: " << p.getJumlahHewan() << endl;

    p.displayGrid();
    p.displayInventory();

    cout << "Memberi makan..." << endl;
    p.memberiPangan();

    delete hewan1;

    return 0;
}
