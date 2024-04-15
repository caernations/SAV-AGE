#ifndef __GAMEMANAGER_HPP__
#define __GAMEMANAGER_HPP__

#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include "../Player/Player.hpp"
#include "../Player/Petani.hpp"
//#include "../Player/Walikota.hpp"
#include "../utils/StringProcessor.hpp"
#include "Codex.hpp"
#include "../Item/GeneralStore.hpp"
#include <fstream>

using namespace std;

// game manager exceptions
class GMException : public exception{
    public:
        GMException();
        GMException(string message);
        ~GMException();
};

class GameManager{
    private:
        int turn;
        string lastInput;
        vector<string> lastMultiInput;
        Store store;
        vector<Player*> activePlayers;
        Codex codex;
        int goldToWin;
        int weightToWin;
        tuple<int,int> invSize;
        tuple<int,int> lahanSize;
        tuple<int,int> ternakSize;
    public:
        string configpath;

        GameManager();

        ~GameManager();
        
        const Codex get_codex();

        //read config
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

        bool checkLastInput(const vector<string>& comparison);

        void saveState(const string& path);

        void loadState(const string& path);

        void awaitMultiInput(char splitter);

        void awaitMultiInput(string question,char splitter);

        void cheat();

        void buyLoop();

        void sellLoop();

        void playerLexSort(vector<Player> playerlist);
};

#endif