#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include "../Player/Player.hpp"
#include "../Player/Petani.hpp"
#include "../utils/StringProcessor.hpp"
#include "Codex.hpp"

using namespace std;

// game manager exceptions
class GMException : public exception{
    public:
        GMException();
        GMException(char* message);
        ~GMException();
};

class GameManager{
    private:
        int turn;
        string lastInput;
        vector<string> lastMultiInput;
        //GeneralStore& store;
        vector<Player*> activePlayers;
        Codex codex;
    public:
        GameManager();

        ~GameManager();
        
        const Codex get_codex();

        //loadfrom
        void load(string savename);

        //startnew
        void init();

        //getter
        string getLastInput();
        vector<string> getLastMultiInput();        

        //initloop adalah loop untuk "main menu"
        void initloop();

        //GameLoop adalah loop utama yang mengandung semua interaksi player-CLI
        //Ada 2 cara untuk tau game udah selesai, return boolean atau throw exception
        void gameloop();

        //Meminta input dan dimasukkan ke variable lastInput
        void awaitLineInput();

        //sama aja tapi nulis text sebelum await cin
        void awaitLineInput(string question);

        void saveState();

        void loadState();

        void awaitMultiInput(char splitter);

        void awaitMultiInput(string question,char splitter);

        void cheat();


};

#endif