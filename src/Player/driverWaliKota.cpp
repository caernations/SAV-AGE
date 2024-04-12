#include "Walikota.hpp"
// #include "Walikota.cpp"
// #include "Player.cpp"
// #include "../Item/Product.cpp"
// #include "../Item/Building.cpp"

// g++ -o test driverWaliKota.cpp Walikota.cpp Player.cpp ../Item/Product.cpp ../Item/Building.cpp ../Item/Item.cpp ../Item/Recipe.cpp ../utils/StringProcessor.cpp

#include <iostream>

int main(){
    Walikota w(1, "Joni", 10, 10, 5, 5);
    Recipe r(1, "SML", "SMALL_HOUSE", 10);
    r.addMaterial("WOOD", 4);
    r.addMaterial("IRON", 1);

    w.addRecipe(r);

    Product p(1, PRODUCT_MATERIAL_PLANT, "TEAK_TREE", 0, "TWD", "WOOD", 1000);
    Product p2(2, PRODUCT_MATERIAL_PLANT, "TEAK_TREE", 0, "TWD", "WOOD", 1000);
    Product p3(3, PRODUCT_MATERIAL_PLANT, "TEAK_TREE", 0, "TWD", "WOOD", 1000);
    Product p4(4, PRODUCT_MATERIAL_PLANT, "TEAK_TREE", 0, "TWD", "WOOD", 1000);
    Product p5(5, PRODUCT_MATERIAL_PLANT, "IRON_PLANT", 0, "TOD", "IRON", 1000);

    w.addToInvEmptySlot(&p);
    w.addToInvEmptySlot(&p2);
    w.addToInvEmptySlot(&p3);
    w.addToInvEmptySlot(&p4);
    w.addToInvEmptySlot(&p5);

    vector<pair<Product*, int>> materials = w.getVarianMaterial();

    w.buildBuilding();
    // w.isEnoughToBuild("SMALL_HOUSE");
    
    cout<<w.getItemCountInInventory()<<endl;
    w.displayGrid();

    

    

}