#ifndef PLANT_HPP
#define PLANT_HPP

#include "Item.hpp"
#include <string>
#include <iostream>
using namespace std;

enum PlantType {
    MATERIAL_PLANT = 1,
    FRUIT_PLANT
};

class Plant :public Item {
    private:
        // Kode unik untuk class Plant
        int plantID;
        // Tipe tanaman
        PlantType plantType;
        // Waktu yang dibutuhkan untuk memanen tanaman
        int duration_to_harvest;

    public:
        // Umur tanaman
        int age;

        // ctor tanpa parameter
        /**
         * Constructor awal dengan age = 0
         * plantID = 0
         * plantType = "",
         * duration_to_harvest = 0 
         * itemCode = ""
         * itemName = ""
         * itemPrice = 0
         */
        Plant();

        // ctor
        /**
        * Constructor awal dengan age = 0
        * @param plantID Kode unik untuk class Plant
        * @param plantType Tipe tanaman
        * @param duration_to_harvest Waktu yang dibutuhkan untuk memanen tanaman
        * @param itemCode Kode unik untuk class Item
        * @param itemName Nama tanaman
        * @param itemPrice Harga tanaman
        */
        Plant(int plantID, const string& itemCode, const string& itemName, const PlantType& plantType, int duration_to_harvest, int itemPrice);

        // dtor
        ~Plant();

        // getter
        /**
         * Mengembalikan kode unik untuk class Plant
         * @return plantID
         */
        int getPlantID() const;

        /**
         * Mengembalikan tipe tanaman
         * @return plantType
         */
        PlantType getPlantType() const;

        /**
         * Mengembalikan waktu yang dibutuhkan untuk memanen tanaman
         * @return duration_to_harvest
         */
        int getDurationToHarvest() const;

        // setter
        /**
         * Mengubah kode unik untuk class Plant
         * @param newPlantID Kode unik baru
         */
        void setPlantID(int newPlantID);

        /**
         * Mengubah tipe tanaman
         * @param newPlantType Tipe tanaman baru
         */
        void setPlantType(const PlantType& newPlantType);

        /**
         * Mengubah waktu yang dibutuhkan untuk memanen tanaman
         * @param newDurationToHarvest Waktu baru
         */
        void setDurationToHarvest(int newDurationToHarvest);

        // Menambahkan setter untuk age
        /**
         * Mengatur umur tanaman
         * @param newAge Umur baru tanaman
         */
        void setAge(int newAge);

        // operator overloads

        /**
         * Membandingkan dua objek Plant
         * @param other Objek Plant lain
         * @return true jika plantID sama, false jika tidak
         */
        bool operator==(const Plant& other) const;

        /**
         * Copy objek Plant
         * @param other Objek Plant lain
         * @return Objek Plant baru
         */
        Plant& operator=(const Plant& other);

        // polymorphic behavior
        /**
         * Menampilkan informasi tanaman
         */
        void displayItem() const override;

        /**
         * Mengembalikan pointer ke objek Plant baru
         * @return Pointer ke objek Plant baru
         */
        Item* cloneItem() const override;

        /**
         * Tanaman sudah bisa dipanen
         * @return true jika age >= duration_to_harvest, false jika tidak
         */
        bool isReadyToHarvest() const;

        void addAge();

};

#endif