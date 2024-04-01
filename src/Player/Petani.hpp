#ifndef PETANI_HPP
#define PETANI_HPP

#include "Player.hpp"
#include "../Map/Map.hpp"
#include "../Item/Plant.hpp"

class Petani : public Player{
    private:
        Map<Plant> lahan;
        int jumlah_tumbuhan;
        int w_lahan;
        int h_lahan;
    public:
        /**
         * Constructor
         */
        Petani();

        /**
         * konstruktor dengan parameter
         * lahan kosong dengan ukuran sesuai dengan config
         * @param playerID id player
         * @param playerName nama player
         * @param gulden jumlah gulden
         * @param berat_badan berat badan
         * @param w_lahan lebar lahan
         * @param h_lahan tinggi lahan
         * @param invenSizeW lebar inventory
         * @param invenSizeH tinggi inventory
         */
        Petani(int playerID, const string& playerName, int gulden, int berat_badan, int w_lahan, int h_lahan, int invenSizeW, int invenSizeH);

        /**
         * dtor
         */
        ~Petani();

        /**
         * Menampilkan lahan yang dimiliki oleh Petani
         */
        void displayLahan();

        /**
         * mengembalikan jumlah tumbuhan yang dimiliki oleh petani
        */
        int getJumlahTumbuhan() const;

        /**
         * mengembalikan lebar lahan
         */
        int getWLahan() const;

        /**
         * mengembalikan tinggi lahan
         */
        int getHLahan() const;

        /**
         * mengembalikan maks tumnbuhan yang bisa ditanam
         */
        int getMaxTumbuhan() const;

        /**
         * menyimpan tumbuhan ke dalam lahan
         * @param lahanX posisi x lahan
         * @param lahanY posisi y lahan
         * @param tumbuhan tumbuhan yang akan ditanam
        */
        void setLahan(int lahanX, int lahanY, Plant* tumbuhan);

        /**
         * mengembalikan lahan yang dimiliki oleh petani
        */
        Map<Plant>& getLahan();

};

#endif