#include "Codex.hpp"
#include "../utils/StringProcessor.hpp"
#include <iostream>
#include <fstream>
using namespace std;

void Codex::addPlant(const Plant& plant){
    plants.push_back(plant);
};
void Codex::addPlant(const vector<string>& list){
    Plant* item = new Plant(atoi(list[0].c_str()),list[1],list[2],list[3],atoi(list[4].c_str()),atoi(list[5].c_str()));
    plants.push_back(*item);
};

// void Codex::addAnimal(const Animal& animal){
//     animals.push_back(animal);
// };
// void Codex::addAnimal(const vector<string>& list){
//     Animal item(atoi(list[0].c_str()),list[1],atoi(list[2].c_str()),list[3],list[4],atoi(list[5].c_str()));
//     animals.push_back(item);
// };

void Codex::addProduct(const Product& product){
    products.push_back(product);
};
void Codex::addProduct(const vector<string>& list){
    Product item(atoi(list[0].c_str()),list[1],list[2],atoi(list[3].c_str()),list[4],list[5],double(atoi(list[6].c_str())));
    products.push_back(item);
};

// void Codex::addBuilding(const Building& building){
//     buildings.push_back(building);
// };
// void Codex::addBuilding(const vector<string>& list){
//     cout << "UNIMPLEMENTED" << endl;
// };

const Item* Codex::getSource(const Item*& thing){
    int i = 0;
    int max = plants.size();
    while(plants[i].getItemName().compare(thing->getItemName()) != 0 && i < max){
        i++;
    }
    if (i<max){
        return &plants[i]; 
    }
    // for(Animal item : animals){
    //     if (item.getItemName().compare(thing->getItemName()) == 0){
    //         return &item;
    //     };
    // }

    return nullptr;
}

const vector<Product> Codex::getProductList(const Item*& thing){
    vector<Product> retval;
        for(Product item : products){
        if (item.getOrigin().compare(thing->getItemName()) == 0){
            retval.push_back(item);
        };
    }

    return retval;
};

void Codex::populatecodex(const string& path){

    ifstream animal(path + "/animal.txt");
    ifstream plant("../config/plant.txt"); //(path + "/plant.txt")
    //string product = path + "/product.txt";
    //string recipe = path + "/recipe.txt";
    
    cout << "OPENING FILE" << endl;
    if (plant.is_open()){
        cout << "STARTING" << endl;
        string line;
        while(getline(animal,line)){
            cout << line << endl;
            addPlant(split(line, ' '));
        }
    }
    else{
        cout << "OPEN FAILED " << path + "/plant.txt" << endl ;
    }
}