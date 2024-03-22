#include "Animal.hpp"
#include <iostream>
#include <memory>

int main() {
    // Create an animal object (cow)
    std::unique_ptr<Animal> cow(new Animal(1, "HERBIVORE", 20, "COW", "COW", 6));

    std::cout << "Before feeding:" << std::endl;
    std::cout << "Animal ID: " << cow->getAnimalID() << std::endl;
    std::cout << "Animal Type: " << cow->getAnimalType() << std::endl;
    std::cout << "Weight to Harvest: " << cow->getWeightToHarvest() << std::endl;
    std::cout << "Weight: " << cow->getWeight() << std::endl;
    std::cout << "Fed Status: " << (cow->isFed() ? "Yes" : "No") << std::endl;

    // Example of feeding the animal with a plant product
    int foodWeight1 = 5;
    std::string foodType1 = "PRODUCT_FRUIT_PLANT"; 
    std::cout << "\nFeed with " << foodType1 << " and weight " << foodWeight1 << std::endl;
    cow->setFed(foodWeight1, foodType1); //

    std::cout << "\nAfter feeding with plant product:" << std::endl;
    std::cout << "Animal ID: " << cow->getAnimalID() << std::endl;
    std::cout << "Animal Type: " << cow->getAnimalType() << std::endl;
    std::cout << "Weight to Harvest: " << cow->getWeightToHarvest() << std::endl;
    std::cout << "Weight: " << cow->getWeight() << std::endl;
    std::cout << "Fed Status: " << (cow->isFed() ? "Yes" : "No") << std::endl;

    // Check kesiapan panen animal
    std::cout << "\nIs animal ready to harvest? " << (cow->isReadyToHarvest() ? "Yes" : "No") << std::endl;
    
    // Kalau animal Herbivore dikasih makan Animal Product
    int foodWeight2 = 15;
    std::string foodType2 = "PRODUCT_ANIMAL"; 
    std::cout << "\nFeed with " << foodType2 << " and weight " << foodWeight2 << std::endl;
    cow->setFed(foodWeight2, foodType2);

    std::cout << "\nAfter feeding with animal product:" << std::endl;
    std::cout << "Animal ID: " << cow->getAnimalID() << std::endl;
    std::cout << "Animal Type: " << cow->getAnimalType() << std::endl;
    std::cout << "Weight to Harvest: " << cow->getWeightToHarvest() << std::endl;
    std::cout << "Weight: " << cow->getWeight() << std::endl;
    std::cout << "Fed Status: " << (cow->isFed() ? "Yes" : "No") << std::endl;

    // Check kesiapan panen animal
    std::cout << "\nIs animal ready to harvest? " << (cow->isReadyToHarvest() ? "Yes" : "No") << std::endl;

    return 0;
}


// HOW TO RUN
// g++ -o driverAnimal Item.cpp Animal.cpp driverAnimal.cpp
// ./driverAnimal
