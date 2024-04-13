#include "EnumConverter.hpp"

map<string,PlantType> StringToPlantType = {
    {"MATERIAL_PLANT" , MATERIAL_PLANT},
    {"FRUIT_PLANT"   , FRUIT_PLANT}
};
map<PlantType,string> PlantTypeToString = {
    {MATERIAL_PLANT,"MATERIAL_PLANT"},
    {FRUIT_PLANT,"FRUIT_PLANT"}
};


map<string,ProductType> StringToProductType {
    {"PRODUCT_MATERIAL_PLANT",PRODUCT_MATERIAL_PLANT},
    {"PRODUCT_FRUIT_PLANT",PRODUCT_FRUIT_PLANT},
    {"PRODUCT_ANIMAL",PRODUCT_ANIMAL}
};
map<ProductType,string> ProductTypeToString {
    {PRODUCT_MATERIAL_PLANT,"PRODUCT_MATERIAL_PLANT"},
    {PRODUCT_FRUIT_PLANT,"PRODUCT_FRUIT_PLANT"},
    {PRODUCT_ANIMAL,"PRODUCT_ANIMAL"}
};

map<string,PlayerType> StringToPlayerType {
    {"PETANI",PETANI},
    {"PETERNAK",PETERNAK},
    {"WALIKOTA",WALIKOTA}
};
map<PlayerType, string> PlayerTypeToString = {
    {PETANI, "PETANI"},
    {PETERNAK, "PETERNAK"},
    {WALIKOTA, "WALIKOTA"}
};

