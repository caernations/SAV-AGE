#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iomanip>
#include <iostream>
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
        Map(){

        };

        // inisialisasi map dengan ukuran tertentu
        Map(int mapX, int mapY){
            this->lebar = lebar;
            this->panjang = panjang;
            map = vector<vector<T*>>(lebar, vector<T*>(panjang, nullptr));
        };

        // the above + name
        Map(int mapX, int mapY, const string& name) : Map(mapX,mapY){
            this->name = name;    
        };

        // print map seperti spek
        void displayMap(){
            iterateAlphabet(panjang);
            print_divider(panjang,5);
            for (int i = 0; i < lebar; i++){
            cout << setw(2) << setfill('0') << i+1 << " ";
            cout << "|";
            for (int j = 0; j < panjang; j++){
                if (map[j][i] == nullptr){
                    cout << "     " << "|";
                } else {
                    cout << " " << map[j][i]->getItemCode() << " " << "|";
                }
            }
            cout << endl;
            print_divider(panjang,5);

            }
        };

        vector<vector<T*>> getMap(){
           return map;
        };

        // meng set suatu item ke map, menerima OBJEK, bukan konstanta
        void set(int x, int y, T* item){
            this->map[x][y] = item;
        };

        //debug tools : cek ukuran map dari ukuran list
        void reportsize(){
            cout << "MAP SIZE " << map.size() << "*" << map[0].size();
        };
        
        void print_divider(int items, int size){
        cout << "   +";
        for (int i = 0; i < items; i++){
            for (int j = 0; j < size; j++){
                cout << "-";
            }
            cout << "+";
        }
        cout << endl;
        };

        void iterateAlphabet(int length){
        char startChar = 'A';
        cout << "    ";
        for (int i = 0; i < length; ++i) {
            cout << "  " <<  static_cast<char>(startChar + i) << "  ";
            cout << " ";
        }
        cout << std::endl;
        };


};
#endif