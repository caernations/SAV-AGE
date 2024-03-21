#include "Map.hpp"
#include <iostream>

using namespace std;

template<class T>
Map<T>::Map(){};

template<class T>
Map<T>::Map(const int& mapX, const int& mapY){
    this->map_size[0] = mapX;
    this->map_size[1] = mapY;

    vector<T*> row;

    for (int i = 0; i < map_size[1]; i++){
        row.push_back(nullptr);
    }
    for (int j = 0; j < map_size[0]; j++){
        this->map.push_back(row);
    }    
}

template<class T>
Map<T>::Map(const int& mapX, const int& mapY, const std::string& name) : Map(mapX,mapY){
    this->name = name;    
}

template<class T>
void Map<T>::reportsize(){
    cout << "MAP SIZE " << map.size() << "*" << map[0].size();
}

template<class T>
void Map<T>::set(const int& x, const int& y, T item){
    this->map[x][y] = &item;
}

void print_divider(int items, int size){
    cout << "*";
    for (int i = 0; i < items; i++){
        for (int j = 0; j < size; j++){
            cout << "-";
        }
        cout << "*";
    }
    cout << endl;
}

template<class T>
void Map<T>::displayMap(){
    print_divider(map_size[0],3);
    for (int i = 0; i < map_size[1]; i++){
        cout << "|";
        for (int j = 0; j < map_size[0]; j++){
            if (map[j][i] == nullptr){
                cout << "***" << "|";
            }
            else{
                cout << map[j][i] << "|";
            }
        }
        cout << endl;
        print_divider(map_size[0],3);
    }
}

int main(){
    cout << "Creating map..." << endl;
    Map<int> peta(2,2);
    cout << "Size :";
    peta.reportsize();
    cout << endl;
    cout << "Setting map..." << endl;
    cout << "Printing map..." << endl;
    peta.displayMap();

    return 0;
}