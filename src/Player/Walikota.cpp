#include "Walikota.hpp"
#include <iostream>
#include "../utils/StringProcessor.hpp"
using namespace std;

        WKException::WKException(){
            message = "Generic WK Exception occured!";
        };
        WKException::WKException(string message){
            this->message = message;
        };
        WKException::~WKException(){};

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

bool Walikota::isAbleToBuild()
{
    for (Recipe& recipe : resep){
        //cout << "RECIPE : " << recipe.getItemName() << endl;
        vector<pair<Product*, int>> materials = getVarianMaterial();
        if (getGulden() - recipe.getItemPrice() < 0){
            continue;
        }

        map<string, int> needs = recipe.getMaterials();
        for (auto& item : materials){
            needs[item.first->getItemName()] = max(0,needs[item.first->getItemName()]-item.second);
        }

        bool canbuild = true;
        for(auto& item : needs){
            if (item.second > 0){
                canbuild = false;
                //cout << "MISSING : " << item.first << " x " << item.second << endl;
            }
        }
            if (canbuild){
                return true;
            }

        }
    return false;
}

bool Walikota::isValidBuildingName(const string &buildingName)
{
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
            Product* product = dynamic_cast<Product*>(getInventory().getMap()[j][i]);
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

vector<tuple<Player*, int>> Walikota::calculateTax(vector<Player *> playerlist)
{
    vector<tuple<Player*, int>> retval;
    int total = 0;

    for (Player* player : playerlist){
        cout << "TAXING " << player->getPlayerName() << endl;
        if (player->getType() != WALIKOTA){
            int tax = player->hitungKekayaan();
            switch (player->getType()){
                case PETANI :
                    tax -= 13;
                    break;
                case PETERNAK :
                    tax -= 11;
                    break;
            }
            float mult;
            if (tax > 500){
                mult = 0.35;
            }
            else if (tax > 50){
                mult = 0.30;
            }
            else if (tax > 25){
                mult = 0.25;
            }
            else if (tax > 6){
                mult = 0.15;
            }
            else{
                mult = 0.05;
            }

            tax = tax * mult;
            if (tax < 0){
                tax = 0;
            }

            player->changeGulden(-tax);
            changeGulden(tax);
            total += tax;
            //lex insertion
            if (retval.empty()){
                retval.push_back(make_tuple(player,tax));
            }
            else{
                auto i = retval.begin();
                //!lexCompare(player->getPlayerName(),get<0>(*i)->getPlayerName()) IN THEORY, karena player list udah lexografik, ini gkk perllu
                while((i != retval.end() && tax <= get<1>(*i))){
                    i++;
                }
                retval.insert(i,make_tuple(player,tax));
            }
            ///print
        }
    };
    cout << "Cring cring cring..." << endl << "Pajak sudah dipungut!" << endl;
            cout << "Berikut adalah detil dari pemungutan pajak:" << endl;

            for (int i = 0; i < retval.size(); i++){
                cout << "   " << i << ". " << get<0>(retval[i])->getPlayerName() << " - " << PlayerTypeToLCase[get<0>(retval[i])->getType()];
                cout << ": " << get<1>(retval[i]) << " gulden" << endl;
            }

            cout << "Negara mendapatkan pemasukan sebesar " << total << " gulden." << endl;
            cout << "Gunakan dengan baik dan jangan dikorupsi ya!" << endl;
    return retval;
}

bool Walikota::isEnoughToBuild(const string& buildingName) {
    Recipe recipe = getRecipe(buildingName);
    vector<pair<Product*, int>> materials = getVarianMaterial();
    int moneyLeft = getGulden() - recipe.getItemPrice();

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

    if (!isAbleToBuild()){
        cout << "Anda tidak bisa membangun apapun!" << endl;
    }
    else{
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
        Recipe* recipe = new Recipe(getRecipe(buildingName));
        map<string, int> needs = recipe->getMaterials();
        changeGulden(-recipe->getItemPrice());

        for(auto it = needs.begin(); it != needs.end();){
            removeFromInv(it->first, it->second);
            ++it;
        }
        addToInvEmptySlot(recipe);

        Player::displayGrid();
        cout << convertToReadable(buildingName, true, false) << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;

    }
    
}



