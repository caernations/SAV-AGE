#include "Petani.hpp"
#include "../Item/Plant.cpp"
#include "Petani.cpp"
#include "../Item/Product.cpp"
#include "../utils/Color.cpp"
#include "../utils/StringProcessor.cpp"
#include "Player.cpp"
#include "../Item/Item.cpp"

// g++ -o driverPetani driverPetani.cpp Petani.cpp ../Map/Map.cpp ../Item/Plant.cpp ../Item/Product.cpp ../utils/StringProcessor.cpp ../utils/Color.cpp Player.cpp

#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<vector<Item*>> inven;
    inven.resize(5);

    for(int i = 0; i < 5; i++){
        inven[i].resize(5,nullptr);
    }

    Petani p(1,"dani",100,50,5,5, 10, 10);
    cout << p.getJumlahTumbuhan() << endl;
    cout << p.getWLahan() << endl;
    cout << p.getHLahan() << endl;
    cout << p.getMaxTumbuhan() << endl;

    Plant* p1 = new Plant(1, "TWD", "TOWOWO", "MATERIAL", 5, 10);
    Plant p2(2, "ASU", "TOWOWO", "MATERIAL", 5, 10);
    Plant p3(3, "MMK", "TOWOWO_BRONTO", "MATERIAL", 5, 10);
    Plant p4(4, "MMK", "TOWOWO_BRONTO", "MATERIAL", 5, 10);
    Plant p5(5, "MMK", "TOWOWO_BRONTO", "MATERIAL", 5, 10);

    p.setLahan(3,2,p1);
    p.addToInvEmptySlot(&p2);
    p.addToInvEmptySlot(&p3);
    p.addToInvEmptySlot(&p4);
    p.addToInvEmptySlot(&p5);
    // Item& item = p.takeFromInv(PLANT);
    p.getInventory().set(3,5,p1);

    
    p3.changeAge(5);
    p4.changeAge(5);
    p.setLahan(0, 0, &p3);
    p.setLahan(0, 1, &p4);
    vector<pair<Item*, int>> varians = p.getVarianItem(PLANT);
    for (pair<Item*, int> item : varians){
        cout << item.first->getItemCode() << " " << item.second << endl;
    }
    vector<pair<Item*, int>> varians2 = p.getVarianReadyToHarvest();

    for (pair<Item*,int> item: varians2){
        cout << item.first->getItemCode() << " " << item.second << endl;
    }

    vector<Product*> products;
    Product* product1 = new Product(1,"MATERIAL", "TOWOWO", 10, "ASU", "TOWOWOBOIII", 1000);
    Product product2(2,"MATERIAL", "TOWOWODD", 10, "ASU", "TOWOWOBOIII", 1000);
    Product product3(3,"MATERIAL", "TOWOWO_BRONTO", 10, "ASU", "TOWOWOBOIII", 1000);

    products.push_back(product1);
    products.push_back(&product2);
    products.push_back(&product3);

    p.budidaya();

    p.panennn(products);

    p.Player::displayGrid();

    // p.displayGrid();
    delete p1;
}