#include "Building.hpp"
#include <iostream>

int main() {
    // materials
    std::vector<std::pair<std::string, int>> houseMaterials = {
        {"Wood", 10},
        {"Stone", 20}
    };

    std::vector<std::pair<std::string, int>> hotelMaterials = {
        {"Brick", 100},
        {"Glass", 200},
        {"Concrete", 300}
    };

    // building
    Building house(1, "HSE", "House", 5000, houseMaterials);
    Building hotel(2, "HTL", "Hotel", 20000, hotelMaterials);

    // building info
    std::cout << "Original Building Information:" << std::endl;
    house.displayItem();
    hotel.displayItem();

    // cloning building
    Item* clonedHouse = house.cloneItem();
    Item* clonedHotel = hotel.cloneItem();

    // cloning info
    std::cout << "\nCloned Building Information:" << std::endl;
    clonedHouse->displayItem();
    clonedHotel->displayItem();

    // cleanup
    delete clonedHouse;
    delete clonedHotel;

    return 0;
}