#include "GameManager.hpp"
#include "../Item/Item.hpp"
#include <iostream>

using namespace std;
//tes await input
int main(){
    bool quit = false;
    GameManager test;

    cout << "STARTING DRIVER" << endl;
    //test
    test.initloop();
    test.gameloop();
}