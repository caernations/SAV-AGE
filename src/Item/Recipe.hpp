#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <map>
#include "Item.hpp"

class Recipe : public Item {
    private:
        std::map<std::string, int> materials;
    public:
        /**
         * ctor recipe
        */
        Recipe();

        /**
         * ctor dengan parameter
         * membuat map materials
         * @param itemID id item
         * @param itemCode kode item
         * @param itemName nama item
         * @param itemPrice harga item
        */
        Recipe(int itemID, const std::string& itemCode, const std::string& itemName, int itemPrice);

        /**
         * dtor
        */
        ~Recipe();

        /**
         * menambahkan material ke dalam map materials
         * @param material material yang akan ditambahkan
         * @param amount jumlah material
        */
        void addMaterial(std::string material, int amount);

        /**
         * menghapus material dari map materials
         * @param material material yang akan dihapus
        */
        void removeMaterial(std::string material);

        /**
         * menampilkan recipe
        */
        void displayItem() const;

        /**
         * apakah material cukup untuk membuat bangunan                                                                                                                                                                         
        */
        bool isEnoughMaterials(int buildingID) const;

        /**
         * mengembalikan jumlah material yang dibutuhkan
         * @param material material yang akan diambil
        */
        int getMaterialAmount(std::string material);

        /**
         * mengembalikan materials
        */
        map<string, int> getMaterials() const;

        Item* cloneItem() const;
        
};

#endif