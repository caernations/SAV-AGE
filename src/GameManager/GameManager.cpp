#include "GameManager.hpp"
#include <exception>

GMException::GMException(){
    cout << "[GameManager] Generic Exception occured!" << endl;
}

GMException::GMException(char* message){
    cout << "[GameManager] Exception : " << message << endl;
}

GMException::~GMException(){}

GameManager::GameManager(){
    //FUNGSI LOADER DISINI
    
    turn = 0;
    lastInput = "";

};

GameManager::~GameManager(){
    cout << "Ending game..." << endl;
};

const Codex GameManager::get_codex(){
    return codex;
}

void GameManager::load(string savename){

};

void GameManager::init(){
    //activePlayers.push_back(new Walikota())
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


void GameManager::initloop(){
    cout << "|| SAV-AGE ||" << endl;
    
    bool getCorrectInput = false;
    while (!getCorrectInput){
        cout << "1. Start new game" << endl;
        cout << "2. Load game" << endl;
        cout << "3. Exit" << endl;
        awaitLineInput(">>>");
        if (lastInput.compare("1") == 0){
            try{
                codex.populatecodex("../config");
                getCorrectInput = true;
                // JANGAN LUPA GANTI KE WALIKOTA KALO UDAH DI FIX
                Player* firstplayer = new Petani(0, "FARMER", 100, 60, 10, 10, 10, 10);
                activePlayers.push_back(firstplayer);
            }
            catch(...){
                cout << "Exception occured!" << endl;
            }   
        }
        
        else if (lastInput.compare("2") == 0){

        }
        else if (lastInput.compare("3") == 0){

        }
        else{
            cout << "Undefined command, please try again" << endl;
        }

    }
};

//cheat menu, if you will
void GameManager::cheat(){
    awaitMultiInput("What is your command?: ",' ');
    string commands[] = {"VIEW","GIVE","TAKE"};
    switch (findIn(lastMultiInput[0],commands,3))
    {
    case 1:
        /* code */
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}

//paling bawah
void GameManager::gameloop(){
    while(true){
        // Wait for input
        awaitLineInput(">>> ");
        
        // Try input
        try{
            // Check with commands
            if (lastInput.compare("EXIT") == 0 || lastInput.compare("QUIT") == 0){
                break;
            }
            else if (lastInput.compare("TAX") == 0){ //TO BE REPLACED WITH SKILL
                cout << "MONEY" << endl;
            }
            else if (lastInput.compare("NEXT") == 0){
                if (activePlayers.size() <= 1){
                    throw string("You are the last man standing");
                }
                else{
                    turn = (turn + 1) % activePlayers.size();
                    cout << "NEXT TURN :" << endl;
                };
            }
            else if (lastInput.compare("CETAK PENYIMPANAN") == 0){
                activePlayers[turn]->displayGrid();
            }
            else if (lastInput.compare("MAKAN") == 0){
                activePlayers[turn]->consumeFromInv();
            }
            else{
                throw string("Invalid command!");
            }
        
        }
        catch (string e){
            cout << e << endl;
        }
        catch (exception e){
            cout << "Exception occured! : " << e.what();
        }

    }
}