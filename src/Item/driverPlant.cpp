#include "Plant.hpp"

using namespace std;

int main(){
    // Plant kosong
    Plant p1;

    Plant p2(1, "P001", "Tomat", "Buah", 30, 5000);

    cout << "Plant ID: " << p2.getPlantID() << endl;

    cout << "Plant Type: " << p2.getPlantType() << endl;

    cout << "Plant Harvest Duration: " << p2.getDurationToHarvest() << endl;

    p1.setPlantID(69);
    cout << "Plant ID: " << p1.getPlantID() << endl;

    p1.setPlantType("Sayur");

    cout << "Plant Type: " << p1.getPlantType() << endl;

    p1.setDurationToHarvest(420);

    cout << "Plant Harvest Duration: " << p1.getDurationToHarvest() << endl;

    if (p1 == p2) {
        cout << "Sama" << endl;
    } else {
        cout << "Tidak Sama" << endl;
    }

    Plant p3 = p2;

    cout << "Plant ID: " << p3.getPlantID() << endl;

    p3.displayItem();

    if (p3.isReadyToHarvest()) {
        cout << "Sudah bisa dipanen" << endl;
    } else {
        cout << "Belum bisa dipanen" << endl;
    }

    Plant p4(2, "P002", "Lettuce", "Sayur", 15, 3000);
    p4.setAge(15);
    p4.displayItem();
    if (p4.isReadyToHarvest()) {
        cout << "Sudah bisa dipanen" << endl;
    } else {
        cout << "Belum bisa dipanen" << endl;
    }


    return 0;
}