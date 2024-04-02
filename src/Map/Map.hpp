#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "../Item/Item.hpp"

using namespace std;

template <class T>
class Map{
    private:
        int panjang; // X axis
        int lebar; // Y axis
        // List yang memegang map
        vector<vector<T*>> map;
        string name;
    public:
        // inisialisasi map kosong
        Map();

        // inisialisasi map dengan ukuran tertentu
        Map(int mapX, int mapY);

        // the above + name
        Map(int mapX, int mapY, const string& name);

        // print map seperti spek
        void displayMap();

        vector<vector<T*>> getMap();

        // meng set suatu item ke map, menerima OBJEK, bukan konstanta
        void set(int x, int y, T* item);

        //debug tools : cek ukuran map dari ukuran list
        void reportsize();
        
        void print_divider(int items, int size);

        void iterateAlphabet(int length);


};
#endif