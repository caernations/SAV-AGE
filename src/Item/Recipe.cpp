#include "Recipe.hpp"
#include "../utils/StringProcessor.hpp"
#include <iostream>
using namespace std;

Recipe::Recipe() : Item(0, "0", "0", 0, RECIPE) {
    materials = std::map<string, int>();
}

Recipe::Recipe(int itemID, const std::string& itemCode, const std::string& itemName, int itemPrice, ItemType itemType) 
:   Item(itemID, itemCode, itemName, itemPrice, itemType) {
    materials = std::map<string, int>();
}

Recipe::~Recipe() {
    materials.clear();
}

void Recipe::addMaterial(string material, int amount) {
    materials[material] = amount;
}

void Recipe::removeMaterial(string material) {
    materials.erase(material);
}

int Recipe::getMaterialAmount(string material) {
    return materials[material];
}

void Recipe::displayItem() const {
    cout << '\t' << this->getItemID() << ". ";
    cout << this->getItemCode();
    cout << " (" << this->getItemPrice() << " gulden,"; 
    for (auto it = materials.begin(); it != materials.end(); it++) {
        cout << " " << convertToReadable(it->first) << " " << it->second;
        if (next(it) != materials.end()) {
            cout << ",";
        }
    }
    cout << ")" << endl;
}

Item* Recipe::cloneItem() const {
    return new Recipe(*this);
}
