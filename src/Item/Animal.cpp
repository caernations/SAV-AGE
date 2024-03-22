#include "Animal.hpp"

// Constructor
Animal::Animal() : Item(0, "", "", 0, ANIMAL), animalID(0), animalType(""), weight_to_harvest(0), weight(0) {}

Animal::Animal(int animalID, const std::string& animalType, int weight_to_harvest, const std::string& itemCode, const std::string& itemName, int itemPrice)
    : Item(0, itemCode, itemName, itemPrice, ANIMAL), animalID(animalID), animalType(animalType), weight_to_harvest(weight_to_harvest), weight(0) {}

// Destructor
Animal::~Animal() {}

// Getters
int Animal::getAnimalID() const {
    return animalID;
}

std::string Animal::getAnimalType() const {
    return animalType;
}

int Animal::getWeightToHarvest() const {
    return weight_to_harvest;
}

int Animal::getWeight() const {
    return weight;
}

bool Animal::isFed() const {
    return fed;
}

// Setters
void Animal::setAnimalID(int newAnimalID) {
    animalID = newAnimalID;
}

void Animal::setAnimalType(const std::string& newAnimalType) {
    animalType = newAnimalType;
}

void Animal::setWeightToHarvest(int newWeightToHarvest) {
    weight_to_harvest = newWeightToHarvest;
}

void Animal::setFed(int foodWeight, const std::string& foodType) {
    std::string animalType = getAnimalType();

    if (animalType == "HERBIVORE") {
        if (foodType == "PRODUCT_MATERIAL_PLANT") {
            std::cout << "Fed Status: Herbivores can't eat material." << std::endl;
        } else if (foodType == "PRODUCT_FRUIT_PLANT") {
            std::cout << "Fed Status: Adding weight for herbivore." << std::endl;
            fed = true;
            weight += foodWeight;
        } else if (foodType == "PRODUCT_ANIMAL") {
            std::cout << "Fed Status: Herbivores don't eat animal products." << std::endl;
        }
    } else if (animalType == "CARNIVORE") {
        if (foodType == "PRODUCT_MATERIAL_PLANT") {
            std::cout << "Fed Status: Carnivores can't eat material." << std::endl;
        } else if (foodType == "PRODUCT_FRUIT_PLANT") {
            std::cout << "Fed Status: Carnivores don't eat plant products." << std::endl;
        } else if (foodType == "PRODUCT_ANIMAL") {
            std::cout << "Fed Status: Adding weight for carnivore." << std::endl;
            fed = true;
            weight += foodWeight;
        }
    } else if (animalType == "OMNIVORE") {
        if (foodType == "PRODUCT_MATERIAL_PLANT") {
            std::cout << "Fed Status: Omnivores can't eat material." << std::endl;
        } else {
            std::cout << "Fed Status: Adding weight for omnivore." << std::endl;
            fed = true;
            weight += foodWeight;
        }
    } else {
        std::cout << "Unhandled" << std::endl;
    }
}

// Operator overloads
bool Animal::operator==(const Animal& other) const {
    return animalID == other.animalID;
}

Animal& Animal::operator=(const Animal& other) {
    animalID = other.animalID;
    animalType = other.animalType;
    weight_to_harvest = other.weight_to_harvest;
    weight = other.weight;
    return *this;
}

// Polymorphic behavior
void Animal::displayItem() const {
    this->Item::displayItem();
    std::cout << "Animal ID: " << animalID << ", Type: " << animalType << ", Harvest Weight: " << weight_to_harvest << ", Weight: " << weight << std::endl;
}

Item* Animal::cloneItem() const {
    return new Animal(*this);
}

// Function
bool Animal::isReadyToHarvest() const {
    return weight >= weight_to_harvest;
}
