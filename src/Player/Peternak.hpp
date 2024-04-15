#ifndef PETANI_HPP
#define PETANI_HPP

#include "Player.hpp"
#include "../Map/Map.hpp"
#include "../Item/Animal.hpp"
#include "../utils/Color.hpp"


class Peternak : public Player {
    private:
        Map<Animal> kandang;
        Map<Item> inventory;
        int jumlah_hewan;
        int w_kandang;
        int h_kandang;
        int maxHewan;
    public:
        /**
         * Constructor
         */
        Peternak();

        /**
         * konstruktor dengan parameter
         * kandang kosong dengan ukuran sesuai dengan config
         * @param playerID id player
         * @param playerName nama player
         * @param gulden jumlah gulden
         * @param berat_badan berat badan
         * @param w_kandang lebar kandang
         * @param h_kandang tinggi kandang
         * @param invenSizeW lebar inventory
         * @param invenSizeH tinggi inventory
         */
        Peternak(int playerID, const string& playerName, int gulden, int berat_badan, int w_kandang, int h_kandang, int invenSizeW, int invenSizeH);

        /**
         * dtor
         */
        ~Peternak();

        /**
         * Menampilkan kandang yang dimiliki oleh Peternak
         */
        void displayGrid();

        /**
         * Menampilkan penyimpanan yang dimiliki oleh Peternak
         */
        void displayInventory();

        /**
         * mengembalikan jumlah hewan yang dimiliki oleh peternak
        */
        int getJumlahHewan() const;

        /**
         * mengembalikan lebar kandang
         */
        int getWKandang() const;

        /**
         * mengembalikan tinggi kandang
         */
        int getHKandang() const;

        /**
         * mengembalikan maks hewan yang bisa diternak
         */
        int getMaxHewan() const;

        /**
         * menyimpan hewan ke dalam kandang
         * @param kandangX posisi x kandang
         * @param kandangY posisi y kandang
         * @param hewan hewan yang akan diternak
        */
        void setKandang(int kandangX, int kandangY, Animal* hewan);
        
        void budidaya();

        void panennn(const vector<Product>& products);

        bool isFoodTypeCompatible(const std::string& animalType, const std::string& foodType);

        void memberiPangan();

        virtual int hitungKekayaan() const override;

        Map<Animal>& getKandang();

        vector<pair<Item*, int>> getVarianReadyToFeed(const std::string& animalType);

        vector<pair<Item*, int>> getVarianReadyToHarvest();
};

#endif