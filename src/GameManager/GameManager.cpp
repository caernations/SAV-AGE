#include "GameManager.hpp"

GameManager::GameManager(){
    //FUNGSI LOADER DISINI
    
    turn = 0;
    lastInput = "";

};

GameManager::~GameManager(){
    cout << "Ending game..." << endl;
};

//get setters
string GameManager::getLastInput(){
    return lastInput;
}
vector<string> GameManager::getLastMultiInput(){
    return lastMultiInput;
}

//awaitLineInput group
void GameManager::awaitLineInput(){
    getline(cin, lastInput);
};

void GameManager::awaitLineInput(string question){
    cout << question;
    getline(cin, lastInput);
}

//awaitMultiInput group
void GameManager::awaitMultiInput(char splitter){
    getline(cin, lastInput);
    lastMultiInput = split(lastInput,splitter);
}

void GameManager::awaitMultiInput(string question,char splitter){
    cout << question;
    getline(cin, lastInput);
    lastMultiInput = split(lastInput,splitter);
}

//paling bawah
void GameManager::gameloop(){
    while(true){

    }
}