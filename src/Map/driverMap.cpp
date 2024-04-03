#include "Map.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

int main(){
    Map<int> m(5,5);
    m.set(0,0, new int(1));
    m.set(0,1, new int(2));
    m.set(0,2, new int(3));
    
    m.displayMap();
    return 0;
}