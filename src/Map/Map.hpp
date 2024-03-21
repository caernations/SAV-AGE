#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include <string>

template <class T>
class Map{
    private:
        // Ukuran map, map_size[0] adalah x, [1] adalah y
        int map_size[2];
        // List yang memegang map
        std::vector<std::vector<T*>> map;

        std::string name;
    public:
        // inisialisasi map kosong
        Map();

        // inisialisasi map dengan ukuran tertentu
        Map(const int& mapX, const int& mapY);

        // the above + name
        Map(const int& mapX, const int& mapY, const std::string& name);

        // print map seperti spek
        void displayMap();

        // meng set suatu item ke map, menerima OBJEK, bukan konstanta
        void set(const int& x, const int& y, T item);

        //debug tools : cek ukuran map dari ukuran list
        void reportsize();
};
#endif