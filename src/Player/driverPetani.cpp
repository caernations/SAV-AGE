#include "Petani.hpp"

// g++ -o driverPetani driverPetani.cpp Petani.cpp ../Item/Item.cpp ../Item/Plant.cpp ../Item/Product.cpp ../utils/StringProcessor.cpp ../utils/Color.cpp Player.cpp

#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<vector<Item*>> inven;
    inven.resize(5);

    for(int i = 0; i < 5; i++){
        inven[i].resize(5,nullptr);
    }

    Petani p(1,"dani", 100, 50 , 5, 5, 10, 10);
    cout << p.getJumlahTumbuhan() << endl;
    cout << p.getWLahan() << endl;
    cout << p.getHLahan() << endl;
    cout << p.getMaxTumbuhan() << endl;
    cout << p.getGulden() << endl;

    Plant* p1 = new Plant(1, "TWD", "TOWOWO", MATERIAL_PLANT, 5, 10);
    Plant p2(2, "ASU", "TOWOWO", MATERIAL_PLANT, 5, 10);
    Plant p3(3, "MMK", "TOWOWO_BRONTO", MATERIAL_PLANT, 5, 10);
    Plant p4(4, "MMK", "TOWOWO_BRONTO", MATERIAL_PLANT, 5, 10);
    Plant p5(5, "MMK", "TOWOWO_BRONTO", MATERIAL_PLANT, 5, 10);

    p.setLahan(3,2,p1);
    p.addToInvEmptySlot(&p2);
    p.addToInvEmptySlot(&p3);
    p.addToInvEmptySlot(&p4);
    p.addToInvEmptySlot(&p5);
    // Item& item = p.takeFromInv(PLANT);
    p.getInventory().set(3,5,p1);

    
    p3.setAge(5);
    p4.setAge(5);
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

    vector<Product> products;
    Product* product1 = new Product(1,PRODUCT_MATERIAL_PLANT, "TOWOWO", 10, "ASI", "TOWOWOBOIII", 1000);
    Product product2(2,PRODUCT_MATERIAL_PLANT, "TOWOWO", 10, "ASI", "TOWOWOBOIII", 1000);
    Product product3(3,PRODUCT_MATERIAL_PLANT, "TOWOWO_BRONTO", 10, "ABU", "TOWOWOBOIII", 1000);

    products.push_back(*product1);
    products.push_back(product2);
    products.push_back(product3);
    
    p.budidaya();
    p.panennn(products);
    p.consumeFromInv();
}