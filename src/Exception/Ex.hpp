#include "Exception.hpp"

using namespace std;

class tes {
    public:
        void emptyInv(){
            throw InventoryEmptyException();
        }
        void fullInv(){
            throw InventoryFullException();
        }
        void fullLahan(){
            throw LahanFullException();
        }
        void noPlantInInv(){
            throw NoPlantInInventoryException();
        }
        void noPlantToHarvest(){
            throw NoPlantToHarvestException();
        }
        void notAbleToBuild(){
            throw NotAbleToBuildException();
        }
        void noFoodInInv(){
            throw NoFoodInInventoryException();
        }
        void fullKandang(){
            throw KandangFullException();
        }
        void noAnimalInInv(){
            throw NoAnimalInInventoryException();
        }
        
};