#include "Plant.hpp"

Plant::Plant() : Item(0," "," ", 0 ,PLANT), plantID(0), plantType(""), duration_to_harvest(0), age(0) {
    cout << "Created empty plant" << endl;
}

Plant::Plant(int plantID, const std::string& itemCode, const std::string& itemName, const std::string& plantType, int duration_to_harvest, int itemPrice) 
    : Item(0, itemCode, itemName, itemPrice, PLANT), plantID(plantID), plantType(plantType), duration_to_harvest(duration_to_harvest), age(0) {
        cout << "Created Plant" << endl;
        cout << "Item ID: " << getItemID() << ", Item Code: " << getItemCode() << ", Item Name: " << getItemName() << ", Item Price: " << getItemPrice() << endl;
        cout << "Plant ID: " << plantID << ", Type: " << plantType << ", Harvest Time: " << duration_to_harvest << ", Age: " << age << endl;
    }

Plant::~Plant() {
    cout << "Deleted Plant" << endl;
}

int Plant::getPlantID() const {
    return plantID;
}

std::string Plant::getPlantType() const {
    return plantType;
}

int Plant::getDurationToHarvest() const {
    return duration_to_harvest;
}

void Plant::setPlantID(int newPlantID) {
    plantID = newPlantID;
}

void Plant::setPlantType(const std::string& newPlantType) {
    plantType = newPlantType;
}

void Plant::setDurationToHarvest(int newDurationToHarvest) {
    duration_to_harvest = newDurationToHarvest;
}

bool Plant::operator==(const Plant& other) const {
    return plantID == other.plantID;
}

Plant& Plant::operator=(const Plant& other) {
    plantID = other.plantID;
    plantType = other.plantType;
    duration_to_harvest = other.duration_to_harvest;
    age = other.age;
    
    return *this;
}

void Plant::displayItem() const {
    std::cout << "Plant ID: " << plantID << ", Type: " << plantType << ", Harvest Time: " << duration_to_harvest << ", Age: " << age << std::endl;
}

Item* Plant::cloneItem() const {
    return new Plant(*this);
}

bool Plant::isReadyToHarvest() const {
    return this->age >= this->getDurationToHarvest();
}

void Plant::changeAge(int newAge){
    age = newAge;
}