
#include "GeneralStore.hpp"
#include "Product.hpp"
#include "Plant.hpp"

int main() {
    cout << "flag1" << endl;
    std::vector<Item*> items;
    std::vector<int> item_quan;


    Product prod1 (1, "PRODUCT_MATERIAL_PLANT", "TEAK_TREE", 0, "TAW", "TEAK_WOOD", 9);
    Product prod2 (11, "PRODUCT_ANIMAL", "HORSE", 8, "HRM", "HORSE_MEAT", 10);
    Plant p2 (1, "P001", "Tomat", "Buah", 30, 5000);

    
    Item* item1 = &prod1;
    Item* item2 = &prod2;
    Item* item3 = &p2;
    //Item* cow = new Animal(1, "HERBIVORE", 20, "COW", "COW", 6);
    
    cout << "flag2" << endl;

    
    

    // Pushing pointers to items vector
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);
    //items.push_back(cow);

    item_quan.push_back(10);
    item_quan.push_back(3);
    item_quan.push_back(-1);

    
    

    // You need to create an instance of Store with non-empty items and item_quan vectors
    Store store(move(items), item_quan);
    cout << endl;
    store.displayStore();

    cout << "flag3" << endl;


    // cek fungsi isinstore 
    int check = store.isinStore(item2);
    cout << check << endl;
    cout << "Is prod1 in store: ";
    std::cout << (check != -1) << endl << endl;

    store.displayStore();

    store.addItem(item1, 10);
    store.addItem(item2, 10);
    store.addItem(item3, 10);

    store.displayStore();

    Item* sold1 = store.sellItem(1, 5);
    Item* sold2 = store.sellItem(2, 5);
    Item* sold3 = store.sellItem(3, 3);

    store.displayStore();

    Product* pr1 = dynamic_cast<Product*>(sold1);
    pr1->displayItem();
    Product* pr2 = dynamic_cast<Product*>(sold2);
    pr2->displayItem();
    Plant* pr3 = dynamic_cast<Plant*>(sold3);
    pr3->displayItem();

    return 0;
}


// how to run (versi rafa)
// g++ -o driverGeneralStore /root/Tubes1_OOP/PetaniPPP/src/Item/Item.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/GeneralStore.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/Product.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/Plant.cpp /root/Tubes1_OOP/PetaniPPP/src/Item/driverGeneralStore.cpp
// ./driverGeneralStore