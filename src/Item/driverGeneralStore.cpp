
#include "GeneralStore.hpp"
#include "Product.hpp"
#include "Plant.hpp"
#include "Animal.hpp"
#include "../Player/Walikota.hpp"
#include "../Player/Petani.hpp"
#include "../Player/Peternak.hpp"

int main() {
    cout << "flag1" << endl;
    std::vector<Item*> items;
    std::vector<int> item_quan;

    Walikota pl1(1, "Joni", 100, 10, 5, 5);
    Petani pl2(2,"dani",100,50,5,5, 10, 10);
    Peternak pl3(3, "Danbull", 100, 50, 5, 5, 10, 10);

    Product prod1 (1, PRODUCT_MATERIAL_PLANT, "TEAK_TREE", 0, "TAW", "TEAK_WOOD", 9);
    Product prod2 (11, PRODUCT_ANIMAL, "HORSE", 8, "HRM", "HORSE_MEAT", 10);
    Plant plant2 (1, "P001", "Tomat", FRUIT_PLANT, 30, 100);
    Animal a1 (1, "HERBIVORE", 20, "COW", "COW", 6);
    
    Item* item1 = &prod1;
    Item* item2 = &prod2;
    Item* item3 = &plant2;
    Item* item4 = &a1;
    Player* p1 = &pl1;
    Player* p2 = &pl2;
    Player* p3 = &pl3;
    //Item* cow = new Animal(1, "HERBIVORE", 20, "COW", "COW", 6);
    
    cout << "flag2" << endl;

    
    

    // Pushing pointers to items vector
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    items.push_back(item4);
    //items.push_back(cow);

    item_quan.push_back(10);
    item_quan.push_back(10);
    item_quan.push_back(-1);
    item_quan.push_back(-1);

    
    

    // You need to create an instance of Store with non-empty items and item_quan vectors
    Store store(move(items), item_quan);
    cout << endl;
    store.displayStore();

    cout << "flag3" << endl;


    // cek fungsi isinstore 
    /*
    int check = store.isinStore(item2);
    cout << check << endl;
    cout << "Is prod1 in store: ";
    std::cout << (check != -1) << endl << endl;

    store.displayStore();
    */


    // cek fungsi add item
    /*
    store.addItem(item1, 10);
    store.addItem(item2, 10);
    store.addItem(item3, 10);
    store.addItem(item4, 10);
    */
    
    //store.displayStore();

    store.BuyAs(p1);

    store.BuyAs(p2);

    store.BuyAs(p3);

    store.BuyAs(p3);
    

    //store.displayStore();

    // Product* pr1 = dynamic_cast<Product*>(sold1);
    // pr1->displayItem();
    // Product* pr2 = dynamic_cast<Product*>(sold2);
    // pr2->displayItem();
    // Plant* pr3 = dynamic_cast<Plant*>(sold3);
    // pr3->displayItem();
    // Animal* pr4 = dynamic_cast<Animal*>(sold4);
    // pr4->displayItem();


    // Item* sold5 = store.sellItem(1, 5, p2);

    //Item* sold6 = store.sellItem(1, 15, 100);

    // store.displayStore();

    // Item* sold7 = store.sellItem(3,2,p2);

    return 0;
}


// how to run (versi rafa)
// g++ -o driverGeneralStore /root/Tubes1_OOP/PetaniPPP/src/Item/Item.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/GeneralStore.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/Product.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/Plant.cpp /root/Tubes1_OOP/PetaniPPP/src/Player/Player.cpp /root/Tubes1_OOP/PetaniPPP/src/Player/Peternak.cpp /root/Tubes1_OOP/PetaniPPP/src/Player/Petani.cpp /root/Tubes1_OOP/PetaniPPP/src/Player/Walikota.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/driverGeneralStore.cpp
// ./driverGeneralStore


// note : displayItem animal cuman bisa kalo this->Item::displayItem(); diilangin