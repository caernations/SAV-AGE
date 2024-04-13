#ifndef __ENUMCONVERVTER_HPP__
#define __ENUMCONVERVTER_HPP__
#include <map>
#include <string>

#include "../Item/Plant.hpp"
extern map<string,PlantType> StringToPlantType;
extern map<PlantType,string> PlantTypeToString;

#include "../Item/Product.hpp"
extern map<string,ProductType> StringToProductType;
extern map<ProductType,string> ProductTypeToString;

#include "../Player/Player.hpp"
extern map<string,PlayerType> StringToPlayerType;
extern map<PlayerType, string> PlayerTypeToString;

#endif