#include "Plant.hpp"

Plant::Plant() : Item(0, "", "", 0), plantID(0), plantType(""), duration_to_harvest(0), age(0) {}

Plant::Plant(int plantID, const std::string& plantType, int duration_to_harvest, const std::string& itemCode, const std::string& itemName, double itemPrice) : Item(0, itemCode, itemName, itemPrice), plantID(plantID), plantType(plantType), duration_to_harvest(duration_to_harvest), age(0) {}

Plant::~Plant() {}

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
    this->Item::displayItem();
    std::cout << "Plant ID: " << plantID << ", Type: " << plantType << ", Harvest Time: " << duration_to_harvest << ", Age: " << age << std::endl;
}

Item* Plant::cloneItem() const {
    return new Plant(*this);
}

bool isReadyToHarvest(const Plant& plant) {
    return plant.age >= plant.getDurationToHarvest();
}




