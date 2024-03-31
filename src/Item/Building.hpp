#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Item.hpp"
#include <vector>
#include <string>
#include <utility>

class Building : public Item {
private:
    std::string buildingCode; 
    std::string buildingName; 
    int buildingID;
    int buildingPrice; 
    std::vector<std::pair<std::string, int>> materials; 

public:
    Building(int buildingID, const std::string& buildingCode, const std::string& buildingName, 
             int buildingPrice, const std::vector<std::pair<std::string, int>>& materials);

    virtual ~Building();

    virtual void displayItem() const override;
    virtual Item* cloneItem() const override;

    std::string getBuildingCode() const;
    std::string getBuildingName() const;
    int getBuildCost() const;
    std::vector<std::pair<std::string, int>> getMaterials() const;
};

#endif 
