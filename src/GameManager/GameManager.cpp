#include "GameManager.hpp"
#include <exception>

GMException::GMException(){
    cout << "[GameManager] Generic Exception occured!" << endl;
}

GMException::GMException(string message){
    cout << "[GameManager] Exception : " << message << endl;
}

GMException::GMException(string message, string context){
    cout << "[GameManager] Exception : " << message << endl;
    cout << "Context : " << context << endl;
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


void GameManager::init(){
    //initialize codex
    codex.populatecodex(configpath);
    //initialize misc
    ifstream misc(configpath + "/misc.txt");
    if (misc.is_open()){
        string line;
        vector<string> multiline;
        getline(misc,line);
        goldToWin = stoi(line);
        getline(misc,line);
        weightToWin = stoi(line);
        getline(misc,line);
        multiline = split(line,' ');
        invSize = {stoi(multiline[0]),stoi(multiline[1])};
        getline(misc,line);
        multiline = split(line,' ');
        lahanSize = {stoi(multiline[0]),stoi(multiline[1])};
        getline(misc,line);
        multiline = split(line,' ');
        ternakSize = {stoi(multiline[0]),stoi(multiline[1])};
    }
    else{
        cout << "OPEN FAILED " << configpath  + "/misc.txt" << endl ;
        throw 1;
    }

    //init shoppe

    for(Plant& item : codex.getPlants()){
        Item* thing = &item;
        store.addItem(thing,-1);
    }
    for(Animal& item : codex.getAnimals()){
        Item* thing = &item;
        store.addItem(thing,-1);
    }

    store.codex = &codex;
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

bool GameManager::checkLastInput(const vector<string>& comparison){
    return isOneOf(lastInput,comparison);
};

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
    cout << "Populating codex..." << endl;
    try{
        init();
    }
    catch(...){
        cout << "Exception occured!";
        throw 1;
    }
    cout << "Load complete!" << endl << endl;

    cout << "|| SAV-AGE ||" << endl;
    
    bool getCorrectInput = false;
    while (!getCorrectInput){
        cout << "1. Start new game" << endl;
        cout << "2. Load game" << endl;
        cout << "3. Exit" << endl;
        awaitLineInput(">>>");
        if (lastInput.compare("1") == 0){
            try{
                getCorrectInput = true;
                // JANGAN LUPA GANTI KE WALIKOTA KALO UDAH DI FIX
                addPlayer("Petani1",40,50,PETANI);
                addPlayer("Peternak1",40,50,PETERNAK);
                addPlayer("Walikota",40,50,WALIKOTA);
            }
            catch(GMException){}
            catch(...){
                cout << "Exception occured!" << endl;
            }   
        }
        
        else if (lastInput.compare("2") == 0){
            awaitLineInput("Save file location from current : ");
            try{
                loadState(lastInput);
                getCorrectInput = true;
                // JANGAN LUPA GANTI KE WALIKOTA KALO UDAH DI FIX
            }
            catch(GMException){}
        }
        else if (lastInput.compare("3") == 0){

        }
        else{
            cout << "Undefined command, please try again" << endl;
        }

    }
};

void GameManager::buyLoop(){
    // Player* actor = activePlayers[turn];
    // store.displayStore();
    // cout << "Uang anda : " << actor->getGulden() << endl;
    // cout << "Slot penyimpanan tersedia : " << actor->getInventory().remainingSlots() << endl;

    // awaitLineInput("Barang yang ingin dibeli : ");
    store.buyAs(activePlayers[turn]);
}

void GameManager::sellLoop(){
    store.sellAs(activePlayers[turn]);
}

void GameManager::playerLexSort(){
    vector<Player*> newlist;
    for(Player* item : activePlayers){
        if(newlist.empty()){
            newlist.push_back(item);
        }
        else{
            auto i = newlist.begin();
            while (i != newlist.end() && !lexCompare(item->getPlayerName(),(*i)->getPlayerName())){
                i++;
            }
            newlist.insert(i,item);
        }
    }
    activePlayers = newlist;
}

void GameManager::nextTick(const int& tickammt){
    for(Player* player : activePlayers){
        if (player->getType() == PETANI){
            Petani* petani = dynamic_cast<Petani*>(player);
            for(Plant* plant : petani->getLahan().convertToList()){
                for (int i = 0; i < tickammt; i++){
                    plant->addAge();
                }
            }
        }
    }
}

void GameManager::addPlayerLoop(){
    awaitMultiInput("Masukkan jenis pemain: ",' ');
    if (lastMultiInput.size() > 1){
        throw GMException("Incorrect type");
    }
    string input = lastMultiInput[0];
    transform(input.begin(),input.end(),input.begin(), ::toupper);
    PlayerType tipe = StringToPlayerType[input];
    if (tipe == 0){
        throw GMException("Internal error when converting to PlayerType",input);
    }
    else if (tipe == WALIKOTA){
        throw GMException("Illegal type!","Cannot have more than 1 walikota");
    }
    awaitMultiInput("Masukkan nama pemain: ",' ');
    if (lastMultiInput.size() > 1){
        throw GMException("Illegal name","Cannot contain spaces");
    }
    Player* newbie = addPlayer(lastMultiInput[0],0,50,tipe);
}

Player* GameManager::addPlayer(const string& name,const int& weight, const int& gold , PlayerType playerType)
{
    Player* player;
    if (playerType == PETANI){
        Petani* petani = (new Petani(0,name,gold,weight,get<1>(lahanSize),get<0>(lahanSize),get<1>(invSize),get<0>(invSize)));
        player = petani;
    }
    else if (playerType == PETERNAK){
        Peternak* peternak = (new Peternak(0,name,gold,weight,get<1>(ternakSize),get<0>(ternakSize),get<1>(invSize),get<0>(invSize)));
        player = peternak;
    }
    else if (playerType == WALIKOTA){
        //add recipes to walikota
        Walikota* wk = new Walikota(0,name,gold,weight,get<1>(invSize),get<0>(invSize));
        for (Recipe& recipes : codex.getBuildings()){
            wk->addRecipe(recipes);
        }
        player = wk;
    }
    else{
        throw GMException("Invalid Player Type!");
    }

    //update turn order
    if (activePlayers.size() > 0) {
        Player* currentplayer = activePlayers[turn];
        activePlayers.push_back(player);
        playerLexSort();
        //update turn thingy
        for (Player* existingplayer : activePlayers){
            if (existingplayer == player){
                turn += 1;
                break;
            }
            else if(existingplayer == currentplayer){
                break;
            }
        }
    }
    else{
        activePlayers.push_back(player);
    }


    //insert to active playerlist and lexsort
    return player;
}

bool GameManager::checkWinners(){
    for (Player* pemain : activePlayers){
        if (pemain->getGulden() > goldToWin){
            cout << "BOOYAH ! Pemain " << pemain->getPlayerName() << " telah memenangkan game dengan meraih lebih dari ";
            cout << goldToWin << " gulden! (" << pemain->getGulden() << ")" << endl;
            return true;
        }
        else if (pemain->getBeratBadan() > weightToWin){
            cout << "BOOYAH ! Pemain " << pemain->getPlayerName() << " telah memenangkan game dengan meraih lebih dari ";
            cout << weightToWin << " KG berat badan! (" << pemain->getBeratBadan() << ")" << endl;
            return true;
        }
    }
    return false;
}

//paling bawah
void GameManager::gameloop(){
    while(true){
        // Wait for input
        awaitLineInput(">>> ");
        
        // Try input
        try{
            // Check with commands
            if (checkLastInput({"EXIT","QUIT"})){
                break;
            }
            else if (checkLastInput({"NEXT"})){
                if (activePlayers.size() <= 1){
                    cout << "You are the last man standing" << endl;
                }
                else{
                    turn = (turn + 1) % activePlayers.size();
                    cout << "NEXT TURN :" << activePlayers[turn]->getPlayerName() << endl;
                };
                nextTick(1);
                cout << "All plants grew by 1!" << endl;
            } 
            else if (checkLastInput({"CETAK_PENYIMPANAN","INVENTORY"})) {
                activePlayers[turn]->Player::displayGrid();
            }
            else if (checkLastInput({"PUNGUT_PAJAK","TAX"}) && activePlayers[turn]->getType() == WALIKOTA){
                Walikota* wk = dynamic_cast<Walikota*>(activePlayers[turn]);
                wk->collectTax(activePlayers);
            }
            else if ((checkLastInput({"CETAK_LADANG","FIELD"})) && activePlayers[turn]->getType() == PETANI){
                activePlayers[turn]->displayGrid();
            }
            else if ((checkLastInput({"CETAK_PETERNAKAN","FARM"})) && activePlayers[turn]->getType() == PETERNAK){
                activePlayers[turn]->displayGrid();
            }
            else if ((checkLastInput({"TANAM"})) && activePlayers[turn]->getType() == PETANI){
                activePlayers[turn]->budidaya();
            }
            else if ((checkLastInput({"TERNAK"})) && activePlayers[turn]->getType() == PETERNAK){
                activePlayers[turn]->budidaya();
            }
            else if ((checkLastInput({"BANGUN","BUILD"})) && activePlayers[turn]->getType() == WALIKOTA){
                Walikota* wk = dynamic_cast<Walikota*>(activePlayers[turn]);
                wk->buildBuilding();
            }
            else if (checkLastInput({"MAKAN"})){
                activePlayers[turn]->consumeFromInv();
            }
            else if (checkLastInput({"KASIH_MAKAN","FEED"})){
                Peternak* farmer = dynamic_cast<Peternak*>(activePlayers[turn]);
                farmer->memberiPangan();
                //activePlayers[turn]->consumeFromInv();
            }
            else if (checkLastInput({"BELI"})){
                buyLoop();
            }
            else if (checkLastInput({"JUAL"})){
                sellLoop();
            }
            else if (checkLastInput({"PANEN"}) && (activePlayers[turn]->getType() == PETANI || activePlayers[turn]->getType() == PETERNAK)){
                activePlayers[turn]->panennn(codex.getProducts());
            }
            else if (checkLastInput({"SAVE","SIMPAN"})){
                saveLoop();
            }
            else if ((checkLastInput({"TAMBAH_PEMAIN"})) && activePlayers[turn]->getType() == WALIKOTA){
                //addPlayerLoop();
                Walikota* wk = dynamic_cast<Walikota*>(activePlayers[turn]);
                tuple<PlayerType,string> newbie = wk->addPlayer(activePlayers);
                addPlayer(get<1>(newbie),0,50,get<0>(newbie));
            }
            else if (checkLastInput({"CHEAT"})){
                try{
                    cheat();
                }
                catch(...){
                    cout << "Incorrect cheat!" << endl;
                }
            }
            else{
                cout << endl << "Invalid command!" << endl;
            }
        
        }
        catch (string e){
            cout << e << endl;
        }
        catch (GMException){

        }
        catch (GameException& e) {
        cout << e.what() << endl;
        }
        catch (exception e){
        cout << "Misc exception catched! : " << e.what() << endl;
        }

        //check money and weight
        if (checkWinners()){
            break;
        }
        
        }
    }