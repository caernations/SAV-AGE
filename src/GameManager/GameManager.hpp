#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

#include <iostream>
#include <vector>
#include <string>
//#include "../Player/Player.hpp"
#include "../utils/StringProcessor.hpp"

using namespace std;

class GameManager{
    private:
        int turn;
        string lastInput;
        vector<string> lastMultiInput;
        //GeneralStore& store;
        //vector<Player> activePlayers;
    public:
        GameManager();

        ~GameManager();
        
        //getter
        string getLastInput();
        vector<string> getLastMultiInput();
        
        //GameLoop adalah loop utama yang mengandung semua interaksi player-CLI
        //Ada 2 cara untuk tau game udah selesai, return boolean atau throw exception
        void gameloop();

        //Meminta input dan dimasukkan ke variable lastInput
        void awaitLineInput();

        //sama aja tapi nulis text sebelum await cin
        void awaitLineInput(string question);


        void awaitMultiInput(char splitter);

        void awaitMultiInput(string question,char splitter);


};

#endif