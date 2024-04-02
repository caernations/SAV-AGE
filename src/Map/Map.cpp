#include "Map.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

template<class T>
Map<T>::Map(){};

template<class T>
Map<T>::Map(int panjang, int lebar){
    this->lebar = lebar;
    this->panjang = panjang;
    map = vector<vector<T*>>(lebar, vector<T*>(panjang, nullptr));
}

template<class T>
Map<T>::Map(int mapX, int mapY, const std::string& name) : Map(mapX,mapY){
    this->name = name;    
}

template<class T>
void Map<T>::reportsize(){
    cout << "MAP SIZE " << map.size() << "*" << map[0].size();
}

template<class T>
void Map<T>::set(int x, int y, T* item){
    this->map[x][y] = item;
}

template<class T>
std::vector<std::vector<T*>> Map<T>::getMap(){
    return map;
}

template<class T>
void Map<T>::displayMap(){
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
}

template<class T>
void Map<T>::print_divider(int items, int size){
    cout << "   +";
    for (int i = 0; i < items; i++){
        for (int j = 0; j < size; j++){
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;
}

template<class T>
void Map<T>::iterateAlphabet(int length) {
    char startChar = 'A';
    cout << "    ";
    for (int i = 0; i < length; ++i) {
        cout << "  " <<  static_cast<char>(startChar + i) << "  ";
        cout << " ";
    }
    cout << std::endl;
}

// int main(){
//     cout << "Creating map..." << endl;
//     Map<int> peta(15,15);
//     cout << "Size :";
//     peta.reportsize();
//     cout << endl;
//     cout << "Setting map..." << endl;
//     cout << "Printing map..." << endl;
//     peta.displayMap();

//     return 0;
// }