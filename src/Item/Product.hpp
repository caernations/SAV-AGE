#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include "Item.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

enum ProductType {
    PRODUCT_MATERIAL_PLANT,
    PRODUCT_FRUIT_PLANT,
    PRODUCT_ANIMAL
};

class Product : virtual public Item {
    private:
        // Kode unik untuk class Product
        int productID;
        // Tipe product
        ProductType productType;
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
        Product(int productId, ProductType productType,string origin,int added_weigth,const string& itemCode, const string& itemName, double itemPrice);
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
        ProductType getProductType() const;

        /**
         * Mengembalikan asal product berupa nama Plant atau Animal
         * @return origin
         */
        string getOrigin() const;

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
        void setProductType(const ProductType& newproductType);

        /**
         * Mengubah origin product
         * @param newOrigin origin baru
         */
        void setOrigin(const string& newOrigin);

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

        /**
         * apakah product sebuah material??
         * @return true jika productType == PRODUCT_MATERIAL_PLANT
        */
        bool isMaterial() const;

        /**
         * konversi ProductType ke string
         * @param productType tipe product
        */
        string convertProductTypeToString(ProductType productType) const;
};
#endif
