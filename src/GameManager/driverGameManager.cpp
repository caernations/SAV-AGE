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

    while(!quit){
        test.awaitLineInput("Your input : ");
        if (test.getLastInput() == "QUIT" || test.getLastInput() == "EXIT"){
            quit = true;
        }
        else{
            cout << "YOU TYPED : " << test.getLastInput() << endl; 
        }
    }
}