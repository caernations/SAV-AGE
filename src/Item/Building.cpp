#include "Building.hpp"
#include "Item.hpp"
#include <iostream>

Building::Building(int buildingID, const std::string& buildingCode, const std::string& buildingName, 
                   int buildingPrice, const std::vector<std::pair<std::string, int>>& materials)
    : Item(buildingID, buildingCode, buildingName, buildingPrice, BUILDING), 
      buildingID(buildingID), buildingCode(buildingCode), 
      buildingName(buildingName), buildingPrice(buildingPrice), materials(materials) {}


Building::~Building() {
}

void Building::displayItem() const {
    std::cout << "Building ID\t\t: " << buildingID 
              << ", Code\t\t\t: " << buildingCode 
              << ", Name\t\t\t: " << buildingName 
              << ", Price\t\t\t: " << buildingPrice << " gulden"
              << ", Materials Required\t: ";

    for (const auto& material : materials) {
        std::cout << material.first << " (x" << material.second << "), ";
    }
    std::cout << std::endl;
}

Item* Building::cloneItem() const {
    return new Building(*this);
}

std::string Building::getBuildingCode() const {
    return buildingCode;
}

std::string Building::getBuildingName() const {
    return buildingName;
}

int Building::getBuildCost() const {
    return buildingPrice;
}

std::vector<std::pair<std::string, int>> Building::getMaterials() const {
    return materials;
}
