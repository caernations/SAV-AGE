#ifndef __CODEX_HPP__
#define __CODEX_HPP__

//highly customizable storage for config results
#include "../Item/Item.hpp"
#include "../Item/Plant.hpp"
#include "../Item/Animal.hpp"
#include "../Item/Product.hpp"
///#include "../Item/Building.hpp"
#include "../Item/Recipe.hpp"
#include "EnumConverter.hpp"
#include <vector>
#include <string>

//PLANT :
//<ID> <KODE_HURUF> <NAME> <TYPE> <DURATION_TO_HARVEST> <PRICE>
//ANIMAL :
//<ID> <KODE_HURUF> <NAME> <TYPE> <WEIGHT_TO_HARVEST> <PRICE>
//PRODUCT :
//<ID> <KODE_HURUF> <NAME> <TYPE> <ORIGIN> <ADDED_WEIGHT> <PRICE>
//RECIPE :
//<ID> <KODE_HURUF> <NAME> <PRICE> <MATERIAL_1> <MATERIAL_1_QUANTITY> <MATERIAL_2> <MATERIAL_2_QUANTITY> ... 

//codex exceptions
class CodexException : public exception{
    public:
        CodexException();
        CodexException(string message);
        CodexException(string message, string context);
        ~CodexException();
};

class Codex{
    private:
        vector<Plant> plants;
        vector<Animal> animals;
        vector<Product> products;
        vector<Recipe> buildings;
    public:
        void addPlant(const Plant& plant);
        void addPlant(const vector<string>& list);

        void addAnimal(const Animal& animal);
        void addAnimal(const vector<string>& list);

        void addProduct(const Product& product);
        void addProduct(const vector<string>& list);

        void addBuilding(const Recipe& building);
        void addBuilding(const vector<string>& list);

        Item* getSource(const Product* thing);
        const vector<Product> getProductList(const Item*& thing);

        void showPlants();
        void showAnimals();
        void showProducts();
        void showBuildings();

        void populatecodex(const string& path);

        Product* getProduct(string name);

        //list getters
        vector<Plant> getPlants() const;
        vector<Animal> getAnimals() const;
        vector<Product> getProducts() const;
        vector<Recipe> getBuildings() const;

        //returns 
        Plant getPlantbyName(string name);
        Animal getAnimalbyName(string name);

        Item* getItemByName(string name);
        Item* getItemReferenceByName(string name);

};

#endif