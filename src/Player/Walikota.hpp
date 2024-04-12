#include "Player.hpp"
#include "../Item/Recipe.hpp"
#include "../utils/StringProcessor.hpp"
#include "../Item/Product.hpp"
#include "../Item/Building.hpp"
#include "../Item/Item.hpp"
#include <vector>
#include <tuple>
#include <iostream>
using namespace std;

class Walikota : public Player {
    private:
        // Daftar resep yang dimiliki oleh Walikota
        vector<Recipe> resep;
    public:
        /**
         * Constructor
        */
        Walikota();

        /**
         * konstruktor dengan parameter
         * @param playerID id player
         * @param playerName nama player
         * @param gulden jumlah gulden
         * @param berat_badan berat badan
        */
        Walikota(int playerID, const string& playerName, int gulden, int berat_badan, int invenW, int invenH);

        /**
         * dtor
        */
        ~Walikota();

        /**
         * Menampilkan resep yang dimiliki oleh Walikota
        */
        void displayRecipe() const;

        /**
         * Menambahkan resep ke dalam daftar resep
         * @param recipe resep yang akan ditambahkan
        */
        void addRecipe(Recipe recipe);

        /**
         * Menghapus resep dari daftar resep
         * @param recipe resep yang akan dihapus
        */
        void removeRecipe(int recipeID);

        /**
         * Membangun bangunan
        */
        void buildBuilding();

        /**
         * apakah walikota mempunyai uang dan material yang cukup untuk membangun salah
         * satu bangunan yang ada
        */
        bool isAbleToBuild();

        /**
         * apakah nama bangunan yang diinputkan valid
        */
        bool isValidBuildingName(const string& buildingName);

        /**
         * apakah mempunyai uang dan material yang cukup untuk membangun bangunan
        */
        bool isEnoughToBuild(const string& buildingName);

        /**
         * Pungut pajak dari pemain lain
        */
        void collectTax();

        /**
         * menambahkan pemain baru ke dalam game
        */
        void addPlayer();

        /**
         * menghapus pemain dari game
        */
        void removePlayer();
        
        /**
         * mengembalikan pair Product dan jumlahnya
         * @return pair product dan item
        */
        vector<pair<Product*, int>> getVarianMaterial();

        /**
         * menghitung pajak untuk tiap pemain
        */
        vector<tuple<string, string, int>> calculateTax(vector<Player> players);

        /**
         * mengurutkan nama player berdasarkan uangnya jika uangnya sama maka
         * diurutkan berdasarkan leksikografis
        */
        vector<Player> sortPlayerTax(vector<tuple<string, string, int>> players);

        Recipe getRecipe(const string& buildingName);

};