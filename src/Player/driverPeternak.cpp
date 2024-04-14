#include "Peternak.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "Starting program..." << endl;
    vector<std::vector<Item*>> inven;
    inven.resize(5);

    for(int i = 0; i < 5; i++){
        inven[i].resize(5,nullptr);
    }

    Peternak p(1, "Dani", 100, 50, 5, 5, 10, 10);

    Animal* hewan1 = new Animal(1, "HERBIVORE", 10, "COW", "Cow", 6);
    Animal hewan2(2, "HERBIVORE", 15, "SHP", "Sheep", 10);
    Animal hewan3(3, "CARNIVORE", 13, "SNK", "Snake", 4);
    Animal hewan4(4, "OMNIVORE", 12, "CHK", "Chicken", 3);
    Animal hewan5(5, "HERBIVORE", 10, "RBT", "Rabbit", 4);
    Product prod1(18, PRODUCT_FRUIT_PLANT, "PEACH_TREE", 5, "PCH", "PEACH", 6);
    Product prod2(19, PRODUCT_ANIMAL, "PIG", 8, "PIG", "PIG_MEAT", 7);

    cout << "Adding hewan to kandang..."  << endl;
    p.setKandang(3, 2, hewan1);
    p.addToInvEmptySlot(&hewan2);
    p.addToInvEmptySlot(&hewan3);
    p.addToInvEmptySlot(&hewan4);
    p.addToInvEmptySlot(&hewan5);
    p.addToInvEmptySlot(&prod1);
    p.addToInvEmptySlot(&prod2);

    p.getInventory().set(3, 5, hewan1);
    p.setKandang(0, 0, &hewan3);
    p.setKandang(0, 1, &hewan4);

    cout << "Jumlah hewan: " << p.getJumlahHewan() + 3 << endl;
    cout << "Lebar kandang: " << p.getWKandang() << endl;
    cout << "Tinggi kandang: " << p.getHKandang() << endl;
    cout << "Maksimum hewan yang bisa diternak: " << p.getMaxHewan() << endl;
    cout << "Jumlah kekayaan: " << p.hitungKekayaan() << endl;
    cout << "BUDIDAYA GUYS" << endl << endl;
    p.budidaya();

    cout << endl;
    cout << "Setelah budidaya, jumlah hewan: " << p.getJumlahHewan() + 3 << endl;

    cout << "Memberi makan..." << endl;
    p.memberiPangan();

    delete hewan1;

    cout << "Ending program..." << endl;
    return 0;
}
