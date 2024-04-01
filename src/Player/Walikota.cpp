#include "Walikota.hpp"
#include <iostream>

Walikota::Walikota() : Player() {
    resep = vector<Recipe>();
}

Walikota::Walikota(int playerID, const string& playerName, int gulden, int berat_badan) : Player(playerID, playerName, gulden, berat_badan) {
    resep = vector<Recipe>();
}

Walikota::~Walikota() {
    resep.clear();
}

void Walikota::displayRecipe() const {
    cout << "Resep bangunan yang ada adalah sebagai berikut." << endl;
    for (int i = 0; i < resep.size(); i++) {
        resep[i].displayItem();
    }
}

void Walikota::addRecipe(Recipe recipe) {
    resep.push_back(recipe);
}

void Walikota::removeRecipe(int recipeID) {
    for (int i = 0; i < resep.size(); i++) {
        if (resep[i].getItemID() == recipeID) {
            resep.erase(resep.begin() + i);
            break;
        }
    }
}

void Walikota::buildBuilding(){
    string buildingName;
    // if (!isEnoughToBuild()) throw NotEnoughRequirementException();
    while(true) {
        cout << "Bangunan yang ingin dibangun: ";
        displayRecipe();
        cout << endl;
        cin >> buildingName;
        if (!isValidBuildingName(buildingName)) {
            cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
            continue;
        }
        else if (!isEnoughToBuild(buildingName)) {
            cout << "Kamu tidak punya cukup bahan untuk membangun bangunan tersebut!" << endl;
            continue;
        }
        else {
            break;
        }
    }
    cout << convertToReadable(buildingName) << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;

}



