#include "Walikota.hpp"
#include <iostream>

Walikota::Walikota() : Player() {
    resep = vector<Recipe>();
}

Walikota::Walikota(int playerID, const string& playerName, int gulden, int berat_badan, int invenW, int invenH) : 
    Player(playerID, playerName, gulden, berat_badan, WALIKOTA, invenW, invenH) {
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

Recipe Walikota::getRecipe(const string& buildingName) {
    for (int i = 0; i < resep.size(); i++) {
        if (resep[i].getItemName() == buildingName) {
            return resep[i];
        }
    }
    return Recipe();
}

bool Walikota::isValidBuildingName(const string& buildingName) {
    for (int i = 0; i < resep.size(); i++) {
        if (resep[i].getItemName() == buildingName) {
            return true;
        }
    }
    return false;
}

vector<pair<Product*, int>> Walikota::getVarianMaterial(){
    vector<pair<Product*, int>> materials;
    for (int i = 0; i < Player::getInvenW(); i++) {
        for (int j = 0; j < getInvenH(); j++) {
            Product* product = dynamic_cast<Product*>(getInventory().getMap()[i][j]);
            if (product != nullptr && product->getItemType() == PRODUCT && product->isMaterial()){
                bool found = false;
                for (auto& item : materials) {
                    if (item.first->getItemCode() == product->getItemCode()) {
                        item.second++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    materials.push_back(make_pair(product, 1));
                }
            }
        }
    }
    return materials;
}

bool Walikota::isEnoughToBuild(const string& buildingName) {
    Recipe recipe = getRecipe(buildingName);
    vector<pair<Product*, int>> materials = getVarianMaterial();
    int moneyLeft = recipe.getItemPrice() - getGulden();

    map<string, int> needs = recipe.getMaterials();
    for (auto it = needs.begin(); it != needs.end();) {
        bool found = false;
        for (const auto& item : materials) {
            if (item.first->getItemName() == it->first) {
                found = true;
                it->second -= item.second;
                if (it->second <= 0) {
                    it = needs.erase(it);
                }
                break;
            }
        }
        if (!found && it != needs.end()) {
            ++it;
        }
    }

    
    if (needs.empty() && moneyLeft <= 0) {
        return true;
    } else {
        cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
        if (moneyLeft > 0) {
            cout << moneyLeft << " gulden";
        }
        if (!needs.empty()) {
            if (moneyLeft > 0) {
                cout << ", ";
            }
            for (auto it = needs.begin(); it != needs.end();) {
                cout << it->second << " " << convertToReadable(it->first, false, false);
                if (++it != needs.end()) {
                    cout << ", ";
                }
            }
        }
        cout <<"!"<< endl;
        return false;
    }
}

void Walikota::buildBuilding(){
    string buildingName;
    // if (!isEnoughToBuild()) throw NotEnoughRequirementException();
    while(true) {
        displayRecipe();
        cout << endl;
        cout << "Bangunan yang ingin dibangun: ";
        cin >> buildingName;
        if (!isValidBuildingName(buildingName)) {
            cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
            continue;
        }
        else if (!isEnoughToBuild(buildingName)) {
            continue;
        }
        else {
            break;
        }
    }
    Recipe recipe = getRecipe(buildingName);
    map<string, int> needs = recipe.getMaterials();
    changeGulden(-recipe.getItemPrice());

    for(auto it = needs.begin(); it != needs.end();){
        removeFromInv(it->first, it->second);
        ++it;
    }
    addToInvEmptySlot(&recipe);

    Player::displayGrid();
    cout << convertToReadable(buildingName, true, false) << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;

}



