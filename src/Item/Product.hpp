#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include "Item.hpp"
#include <string>
#include <iostream>

class Product : public Item
{
private:
    // Kode unik untuk class Product
    int productID;
    // Tipe product
    std::string productType;
    // Asal material (product/Animal)
    std::string origin;
    // Berat yang ditambahkan per konsumsi
    


public:

    int added_weigth;

    // ctor tanpa parameter
    /**
     * Constructor awal dengan
     * productID = 0
     * productType = "",
     * origin = "",
     * added_weight = 0 
     * itemCode = ""
     * itemName = ""
     * itemPrice = 0
     */
    Product();

    // ctor
    /**
    * @param productID Kode unik untuk class product
    * @param productType Tipe product
    * @param origin asal product berupa nama Plant atau Animal
    * @param added_weight Jumlah berat yang diperoleh saat mengonsumsi produk
    * @param itemCode Kode unik untuk class Item
    * @param itemName Nama tanaman
    * @param itemPrice Harga tanaman
    */
    Product(int productId,std::string productType,std::string origin,int added_weigth,const std::string& itemCode, const std::string& itemName, double itemPrice);
    ~Product();

    // getter
    /**
     * Mengembalikan kode unik untuk class product
     * @return productID
     */
    int getProductID() const;

    /**
     * Mengembalikan tipe tanaman
     * @return productType
     */
    std::string getProductType() const;

    /**
     * Mengembalikan asal product berupa nama Plant atau Animal
     * @return origin
     */
    std::string getOrigin() const;

    /**
     * Mengembalikan banyak berat yang diberikan saat mengonsumsi produk
     * @return duration_to_harvest
     */
    int getAddedWeight() const;

    // setter
    /**
     * Mengubah kode unik untuk class product
     * @param newproductID Kode unik baru
     */
    void setProductID(int newproductID);

    /**
     * Mengubah tipe tanaman
     * @param newproductType Tipe tanaman baru
     */
    void setProductType(const std::string& newproductType);

    /**
     * Mengubah origin product
     * @param newOrigin origin baru
     */
    void setOrigin(const std::string& newOrigin);

    /**
     * Mengubah added weigth
     * @param newAddedWeigth Added Weigth baru
     */
    void setAddedWeigth(int newAddedWeigth);

    // operator overloads

    /**
     * Membandingkan dua objek product
     * @param other Objek product lain
     * @return true jika productID sama, false jika tidak
     */
    bool operator==(const Product& other) const;

    /**
     * Copy objek product
     * @param other Objek product lain
     * @return Objek product baru
     */
    Product& operator=(const Product& other);

    // polymorphic behavior
    /**
     * Menampilkan informasi produk
     */
    void displayItem() const;

    /**
     * Mengembalikan pointer ke objek product baru
     * @return Pointer ke objek product baru
     */
    Item* cloneItem() const;

    /**
     * Product bisa dikonsumsi
     * @return true jika added_weight > 0, false jika tidak
     */
    bool isProductConsumable() const;
};

#endif
