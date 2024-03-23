#ifndef PLANT_HPP
#define PLANT_HPP

#include "Item.hpp"
#include <string>
#include <iostream>
using namespace std;

class Plant : public Item {
private:
    // Kode unik untuk class Plant
    int plantID;
    // Tipe tanaman
    std::string plantType;
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
    Plant(int plantID, const std::string& itemCode, const std::string& itemName, const std::string& plantType, int duration_to_harvest, int itemPrice);

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
    std::string getPlantType() const;

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
    void setPlantType(const std::string& newPlantType);

    /**
     * Mengubah waktu yang dibutuhkan untuk memanen tanaman
     * @param newDurationToHarvest Waktu baru
     */
    void setDurationToHarvest(int newDurationToHarvest);

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
    void displayItem() const;

    /**
     * Mengembalikan pointer ke objek Plant baru
     * @return Pointer ke objek Plant baru
     */
    Item* cloneItem() const;

    /**
     * Tanaman sudah bisa dipanen
     * @return true jika age >= duration_to_harvest, false jika tidak
     */
    bool isReadyToHarvest() const;

};

#endif