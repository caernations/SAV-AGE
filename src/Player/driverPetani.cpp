#include "Petani.hpp"
#include "Petani.cpp"
#include "Player.cpp"
#include "../Map/Map.cpp"
#include "../Item/Plant.cpp"
#include "../Item/Product.cpp"
#include "../utils/StringProcessor.cpp"


#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<vector<Item*>> inven;
    inven.resize(5);

    for(int i = 0; i < 5; i++){
        inven[i].resize(5,nullptr);
    }

    Petani p(1,"Petani",100,50,5,5, 10, 10);
    cout << p.getJumlahTumbuhan() << endl;
    cout << p.getWLahan() << endl;
    cout << p.getHLahan() << endl;
    cout << p.getMaxTumbuhan() << endl;

    Plant* p1 = new Plant(1, "TWD", "TOWOWO", "MATERIAL", 5, 10);
    Plant p2(2, "ASU", "TOWOWO", "MATERIAL", 5, 10);
    Plant p3(3, "MMK", "TOWOWO", "MATERIAL", 5, 10);
    p.setLahan(3,2,p1);
    p.addToInv(&p2);
    p.addToInv(&p3);
    Item& item = p.takeFromInv(PLANT);
    cout << item.getItemCode() << endl;
    p.getInventory().set(3,5,p1);
    vector<pair<Item*, int>> varians = p.getVarianItem();
    for (pair<Item*, int> item : varians){
        cout << item.first->getItemCode() << " " << item.second << endl;
    }
    p.displayInventory();
    p.displayLahan();
    delete p1;
}