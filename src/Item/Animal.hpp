#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Item.hpp"
#include <string>
#include <iostream>

class Animal : public Item {
private:
    // Kode unik untuk class Animal
    int animalID;
    // Tipe animal
    std::string animalType;
    // Berat yang dibutuhkan agar animal siap panen
    int weight_to_harvest;
    // Status pemberian makan kepada animal
    bool fed;

public:
    // Berat animal
    int weight;

    // ctor tanpa parameter
    /**
     * Constructor awal dengan age = 0
     * animalID = 0
     * animalType = "",
     * wight_to_harvest = 0 
     * itemCode = ""
     * itemName = ""
     * itemPrice = 0
     */
    Animal();

    // ctor
    /**
    * Constructor awal dengan age = 0
    * @param animalID Kode unik untuk class Animal
    * @param animalType Tipe tanaman
    * @param weight_to_harvest Waktu yang dibutuhkan untuk memanen tanaman
    * @param itemCode Kode unik untuk class Item
    * @param itemName Nama animal
    * @param itemPrice Harga animal
    */
    Animal(int animalID, const std::string& animalType, int weight_to_harvest, const std::string& itemCode, const std::string& itemName, int itemPrice);

    // dtor
    ~Animal();

    // getter
    /**
     * Mengembalikan kode unik untuk class Animal
     * @return animalID
     */
    int getAnimalID() const;

    /**
     * Mengembalikan tipe animal
     * @return animalType
     */
    std::string getAnimalType() const;

    /**
     * Mengembalikan berat yang dibutuhkan agar animal siap panen
     * @return weight_to_harvest
     */
    int getWeightToHarvest() const;

    /**
     * Mengembalikan berat animal saat ini
     * @return weight
     */
    int getWeight() const;

    /**
     * Mengembalikan status apakah animal sudah diberi pangan atau belum
     * @return fed
     */
    bool isFed() const;

    // setter
    /**
     * Mengubah kode unik untuk class Animal
     * @param newAnimalID Kode unik baru
     */
    void setAnimalID(int newAnimalID);

    /**
     * Mengubah tipe animal
     * @param newAnimalType Tipe animal baru
     */
    void setAnimalType(const std::string& newAnimalType);

    /**
     * Mengubah berat yang dibutuhkan agar animal siap panen
     * @param newWeightToHarvest Berat baru
     */
    void setWeightToHarvest(int newWeightToHarvest);

    /**
     * Tambahkan berat animal setelah diberi pangan, lalu set status pemberian makan pada animal
     * @param foodWeight Berat makanan yang diberikan
     */
    void setFed(int foodWeight, const std::string& foodType);

    // operator overloads

    /**
     * Membandingkan dua objek Animal
     * @param other Objek Animal lain
     * @return true jika animalID sama, false jika tidak
     */
    bool operator==(const Animal& other) const;

    /**
     * Copy objek Animal
     * @param other Objek Animal lain
     * @return Objek Animal baru
     */
    Animal& operator=(const Animal& other);

    // polymorphic behavior
    /**
     * Menampilkan informasi animal
     */
    void displayItem() const;

    /**
     * Mengembalikan pointer ke objek Animal baru
     * @return Pointer ke objek Animal baru
     */
    Item* cloneItem() const;

    /**
     * Animal sudah bisa dipanen
     * @return true jika weight >= weight_to_harvest, false jika tidak
     */
    bool isReadyToHarvest() const;

};

#endif
