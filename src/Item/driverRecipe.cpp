#include "Recipe.hpp"
// #include "Recipe.cpp"
// #include "../utils/StringProcessor.cpp"
// #include "Item.cpp"
#include <iostream>
using namespace std;

int main(){
    Recipe r(1, "RCP001", "Recipe 1", 1000, RECIPE);
    r.addMaterial("Material 1", 10);
    r.addMaterial("Material 2", 20);
    r.addMaterial("Material 3", 30);
    cout << r.getMaterialAmount("Material 1") << endl;
    r.displayItem();
    cout << r.getMaterialAmount("Material 1") << endl;
    cout << r.getMaterialAmount("Material 2") << endl;
    cout << r.getMaterialAmount("Material 3") << endl;
    r.removeMaterial("Material 1");
    r.displayItem();
    cout << r.getMaterialAmount("Material 1") << endl;
    cout << r.getMaterialAmount("Material 2") << endl;
    cout << r.getMaterialAmount("Material 3") << endl;
    return 0;
}