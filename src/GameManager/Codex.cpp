#include "Codex.hpp"
#include "../utils/StringProcessor.hpp"
#include <iostream>
#include <fstream>
using namespace std;

CodexException::CodexException(){
    cout << "[Codex] Generic Exception occured!" << endl;
}

CodexException::CodexException(string message){
    cout << "[Codex] Exception : " << message << endl;
}
CodexException::CodexException(string message, string context){
    cout << "[Codex] Exception : " << message << endl;
    cout << "Context : " << context << endl;
};

CodexException::~CodexException(){}


void Codex::addPlant(const Plant& plant){
    plants.push_back(plant);
};
void Codex::addPlant(const vector<string>& list){
    Plant item(atoi(list[0].c_str()),list[1],list[2],StringToPlantType[list[3]],atoi(list[4].c_str()),atoi(list[5].c_str()));
    plants.push_back(item);
};

void Codex::addAnimal(const Animal& animal){
    animals.push_back(animal);
};
void Codex::addAnimal(const vector<string>& list){
    Animal item(atoi(list[0].c_str()),list[3],atoi(list[4].c_str()),list[1],list[2],atoi(list[5].c_str()));
    animals.push_back(item);
};

void Codex::addProduct(const Product& product){
    products.push_back(product);
};
void Codex::addProduct(const vector<string>& list){
    Product item(atoi(list[0].c_str()),StringToProductType[list[3]],list[4],atoi(list[5].c_str()),list[1],list[2],double(atoi(list[6].c_str())));
    products.push_back(item);
};


//quirk : Buildings are stored as Recipes, basically the same
void Codex::addBuilding(const Recipe& building){
    buildings.push_back(building);
};
void Codex::addBuilding(const vector<string>& list){
    if (list.size()%2 == 1){ //ganjil
        throw CodexException("Building missing ammount or material name");
    }
    //vector<pair<string,int>> materials;
    Recipe item(atoi(list[0].c_str()),list[1],list[2],atoi(list[3].c_str()));
    for (int i = 4; i < list.size(); i+=2){
        //materials.push_back({list[i],atoi(list[i+1].c_str())});
        if (getItemByName(list[i]) == nullptr){
            throw CodexException("Item doesnt exist!",list[i]);
        }
        item.addMaterial(list[i],atoi(list[i+1].c_str()));
    };
    //Building item(atoi(list[0].c_str()),list[1],list[2],atoi(list[3].c_str()),materials);
    buildings.push_back(item);
};

Item* Codex::getSource(const Product* thing){
    int i = 0;
    int max = plants.size();
    while(plants[i].getItemName().compare(thing->getOrigin()) != 0 && i < max){
        i++;
    }
    if (i<max){
        return &(plants[i]); 
    }
    for(Animal& item : animals){
        if (item.getItemName().compare(thing->getOrigin()) == 0){
            return &item;
        };
    }

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

void Codex::showPlants() {
    cout << "LIST OF PLANTS :" << endl;
    for (Plant& item : plants){
        cout << item.getItemID() << " ";
        cout << item.getItemCode() << " ";
        cout << item.getItemName() << " ";

        //find string from enum value
        // auto i = StringToPlantType.begin();
        // for( i ; i->second != item.getPlantType(); i++);
        // cout << i->first << " ";
        cout << PlantTypeToString[item.getPlantType()] << " ";

        cout << item.getDurationToHarvest() << " ";
        cout << item.getItemPrice() << endl;
    }
};
void Codex::showAnimals() {
    cout << "LIST OF PLANTS :" << endl;
    for (Animal& item : animals){
        cout << item.getItemID() << " ";
        cout << item.getItemCode() << " ";
        cout << item.getItemName() << " ";

        //find string from enum value
        cout << item.getAnimalType() << " ";

        cout << item.getWeightToHarvest() << " ";
        cout << item.getItemPrice() << endl;
    }
}

// };
void Codex::showProducts() {
    cout << "LIST OF PRODUCTS :" << endl;
    for (Product& item : products){
        cout << item.getItemID() << " ";
        cout << item.getItemCode() << " ";
        cout << item.getItemName() << " ";

        //find string from enum value
        // auto i = StringToProductType.begin();
        // for( i ; i->second != item.getProductType(); i++);
        // cout << i->first << " ";
        cout << ProductTypeToString[item.getProductType()] << " ";

        cout << item.getOrigin() << " ";
        cout << item.added_weigth << " ";
        cout << item.getItemPrice() << endl;
    }
};

void Codex::showBuildings() {
    cout << "LIST OF BUILDINGS :" << endl;
    for (Recipe& item : buildings){
        item.displayItem();
    }
};


void Codex::populatecodex(const string& path){

    ifstream plant(path + "/plant.txt");
    ifstream animal(path + "/animal.txt");
    ifstream product(path + "/product.txt");
    ifstream building(path + "/recipe.txt");
    
    cout << "OPENING PLANTS" << endl;
    if (plant.is_open()){
        cout << "STARTING" << endl;
        string line;
        while(getline(plant,line)){
            cout << line << endl;
            addPlant(split(line, ' '));
        }
    }
    else{
        cout << "OPEN FAILED " << path + "/plant.txt" << endl ;
        throw 1;
    }

    cout << "OPENING ANIMALS" << endl;
    if (animal.is_open()){
        cout << "STARTING" << endl;
        string line;
        while(getline(animal,line)){
            cout << line << endl;
            addAnimal(split(line, ' '));
        }
    }
    else{
        cout << "OPEN FAILED " << path + "/animal.txt" << endl ;
        throw 1;
    }

    cout << "OPENING PRODUCTS" << endl;
    if (product.is_open()){
        cout << "STARTING" << endl;
        string line;
        while(getline(product,line)){
            cout << line << endl;
            addProduct(split(line, ' '));
        }
    }
    else{
        cout << "OPEN FAILED " << path + "/product.txt" << endl ;
        throw 1;
    }

    cout << "OPENING BUILDINGS" << endl;
    if (building.is_open()){
        cout << "STARTING" << endl;
        string line;
        while(getline(building,line)){
            cout << line << endl;
            addBuilding(split(line, ' '));
        }
    }
    else{
        cout << "OPEN FAILED " << path + "/recipe.txt" << endl ;
        throw 1;
    }

    plant.close();
    animal.close();
    product.close();
    building.close();
}

Product* Codex::getProduct(string name){
    for (Product& item : products){
        if (name.compare(item.getItemName()) == 0 || name.compare(item.getItemCode()) == 0){
            return &item;
        }
    }
    return nullptr;
};

Plant Codex::getPlantbyName(string name){
    for (Plant& item : plants){
        if (item.getItemName().compare(name) == 0){
            return item;
        }
    }
    throw CodexException("Invalid animal name!",name);
}

Animal Codex::getAnimalbyName(string name)
{
        for (Animal& item : animals){
        if (item.getItemName().compare(name) == 0){
            return item;
        }
    }
    throw 1;
}

Item* Codex::getItemByName(string name){
    for(Plant& plant : plants){
        if (plant.getItemName().compare(name) == 0){
            Plant* item = new Plant(plant);
            return item;
        }
    }
    for(Animal& animal : animals){
        if (animal.getItemName().compare(name) == 0){
            Animal* item = new Animal(animal);
            return item;
        }
    }
    for(Product& product : products){
        if (product.getItemName().compare(name) == 0){
            Product* item = new Product(product);
            return item;
        }
    }
    for(Recipe& building : buildings){
        if (building.getItemName().compare(name) == 0){
            Recipe* item = new Recipe(building);
            return item;
        }
    }
    throw CodexException("Item not found!");
}

Item *Codex::getItemReferenceByName(string name)
{
    for(Plant& plant : plants){
        if (plant.getItemName().compare(name) == 0){
            return &plant;
        }
    }
    for(Animal& animal : animals){
        if (animal.getItemName().compare(name) == 0){
            return &animal;
        }
    }
    for(Product& product : products){
        if (product.getItemName().compare(name) == 0){
            return &product;
        }
    }
    for(Recipe& building : buildings){
        if (building.getItemName().compare(name) == 0){
            return &building;
        }
    }
    throw CodexException("Item not found!");
}

//getters

vector<Plant> Codex::getPlants() const{
    return plants;
};
vector<Animal> Codex::getAnimals() const{
    return animals;
};
vector<Product> Codex::getProducts() const{
    return products;
};
vector<Recipe> Codex::getBuildings() const{
    return buildings;
};
