#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <utility>
#include "../Item/Item.hpp"
#include "../Map/Map.hpp"
#include "../Item/Product.hpp"
#include "../utils/StringProcessor.hpp"
#include "../Exception/Exception.hpp"

using namespace std;

enum PlayerType {
    PETANI = 1,
    PETERNAK,
    WALIKOTA
};

class Player {
    private:
        const int STARTING_WEIGHT = 40;
        const int STARTING_GULDEN = 50;
        PlayerType playerType;
        int playerID;
        string playerName;
        int gulden;
        int beratBadan;
        Map<Item> inventory; 
        int invenSizeW;
        int invenSizeH;
        int maxItemInInventory;
        int itemCountInInventory;
    public:
        Player();

        Player(int playerID, const string& playerName, int gulden, int berat_badan, PlayerType playerType, int invenSizeW, int invenSizeH);

        virtual ~Player();

        /**
         * mengganti jumlah gulden player
         * @param guldenAmount jumlah gulden yang ingin ditambah/dikurangi
         * guldenAmount positif jika ingin menambahkan gulden
         * guldenAmount negatif jika ingin mengurangi gulden
        */
        void changeGulden(int guldenAmount);

        /**
         * Menambahkan item ke dalam inventory ke slot yang kosong
         * @param item item yang ingin ditambahkan
        */
        void addToInvEmptySlot(Item* item);

        /**
         * Menambahkan item ke dalam inventory pada slot tertentu
         * @param item item yang ingin ditambahkan
         * @param invenX
         * @param invenY
        */
        void addToInvSpecific(Item* item);

        /**
         * Menambahkan item ke inventory dengan pilihan opsi
         * @param item item yang ingin ditambahkan
        */
        void addToInv(Item* item);

        /**
         * Mengambil item dari invento-ry
         * @param ItemType tipe item yang ingin diambil
         * @return item yang diambil
        */
        Item& takeFromInv(ItemType ItemType);

        /**
         * Memakan makanan dari inventory
         * hanya dapat memakan makanan yang memiliki added_weight lebih dari 0
        */
        void consumeFromInv();
        
        /**
         * menghapus item pada inventory
         * @param itemCode item yang ingin dihapus
        */
        void removeFromInv(const string& itemName, int amount);

        /**
         * Menampilkan inventory player
        */
        virtual void displayGrid();

        /**
         * mengubah berat badan pemain
         * @param addedWeight
        */
        void addWeight(int addedWeight);

        // getter
        /**
         * Mendapatkan item dan jumlahnya dari inventory
         * @return vector<pair<Item*, int>> vector yang berisi pasangan item dan jumlahnya
        */
        vector<pair<Item*, int>> getVarianItem(ItemType ItemType);

        /**
         * Mengembalikan inventory player
         * @return Map<Item>& inventory player
        */
        Map<Item>& getInventory();

        /**
         * Mengembalikan lebar inventory
         * @return int lebar inventory player
        */
        int getInvenW();

        /**
         * Mengembalikan tinggi inventory
         * @return int tinggi inventory player
        */
        int getInvenH();

        /**
         * Mengembalikan gulden player
         * @return int gulden player
        */
        int getGulden() const;

        /**
         * Mengembalikan berat badan player
         * @return int berat badan player
        */
        int getBeratBadan() const;

        /**
         * Mengembalikan nama player
         * @return string nama player
        */
        string getPlayerName() const;

        /**
         * Mengembalikan tipe player dalam string
         * @return string tipe player dalam string
        */
        string playerTypeToString() const;

        /**
         * Mengembalikan id player
         * @return int id player
        */
        int getPlayerID() const;

        /**
         * Mengembalikan jumlah item maksimal yang dapat dimiliki player
         * @return int jumlah item maksimal yang dapat dimiliki player
        */
        int getMaxItemInInventory() const;

        /**
         * Mengembalikan jumlah item yang dimiliki player
         * @return int jumlah item yang dimiliki player
        */
        int getItemCountInInventory() const;

        /**
         * Menampilkan info player
        */
        void displayPlayerInfo() const;

        /**
         * Mengembalikan tipe player
         * @return PlayerType tipe player
        */
        PlayerType getType() const;

        /**
         * Mengembalikan apakah inventory player penuh
         * @return bool true jika inventory player penuh
         * false jika inventory player tidak penuh
        */
        bool isInventoryFull();

        /**
         * Mengembalikan apakah inventory player kosong
         * @return bool true jika inventory player kosong
        */
        bool isInventoryEmpty();

        /**
         * apakah terdapat makanan di inventory
         * @return bool true jika terdapat makanan di inventory
        */
        bool isThereFood();

        /**
         * Mengembalikan apakah inventory player memiliki item
         * @return bool true jika inventory player memiliki item
        */
        string itemTypeToString(ItemType type);

        /**
         * Mengembalikan apakah inventory player memiliki item
         * @return bool true jika inventory player memiliki item
        */
        virtual int hitungKekayaan() const;

        /**
         * budidaya mahkluk hidup
        */
        virtual void budidaya();

        /**
         * panen mahkluk hidup
        */
        virtual void panennn(const vector<Product>& products);

        void updateItemCount();
    };

#endif 