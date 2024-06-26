#include "GameManager.hpp"


//SAVESTATE AND LOADSTATE
void GameManager::saveLoop(){
    awaitLineInput("Masukkan lokasi berkas save >>> ");
    try{
        saveState(lastInput);
    }catch(GMException e){

    }
}

void GameManager::saveState(const string& path){
    int playerCount = activePlayers.size();
    //string filename = "testsave.txt";
    ofstream writer(path);
    if (!writer.is_open()){
        throw GMException("Failed to save",path);
    }
    //write player count
    writer << playerCount << endl;
    //write player state
    for(Player* player : activePlayers){
        writer << player->getPlayerName() << " ";
        writer << PlayerTypeToLCase[player->getType()] << " ";
        writer << player->getBeratBadan() << " ";
        writer << player->getGulden() << endl;

        //write inventory
        writer << player->getInventory().convertToList().size() << endl;
        for (Item* item : player->getInventory().convertToList()){
            writer << item->getItemName() << endl;
        }

        switch(player->getType()){
            case(PETANI) : {
                //jumlah tanaman di ladang
                Petani* petani = dynamic_cast<Petani*>(player);
                writer << petani->getLahan().convertToList().size() << endl;
                cout << "Converting to list..." << endl;
                vector<pair<tuple<int,int>,Plant*>> field = petani->getLahan().convertToPositionList();
                cout << "Writing plants..." << endl;
                for (pair<tuple<int,int>,Plant*> plant : field){
                    writer << coordinateToString(plant.first) << " ";
                    writer << plant.second->getItemName() << " ";
                    writer << plant.second->age << endl;
                }
                break;
            }
            case(PETERNAK) : {
                //jumlah tanaman di ladang
                Peternak* peternak = dynamic_cast<Peternak*>(player);
                writer << peternak->getKandang().convertToList().size() << endl;
                cout << "Converting to list..." << endl;
                vector<pair<tuple<int,int>,Animal*>> field = peternak->getKandang().convertToPositionList();
                cout << "Writing animals..." << endl;
                for (pair<tuple<int,int>,Animal*> animal : field){
                    writer << coordinateToString(animal.first) << " ";
                    writer << animal.second->getItemName() << " ";
                    writer << animal.second->getWeight() << endl;
                }
                break;
            }
            case(WALIKOTA) : {
                break;
            }
            default : {
                break;
            }
        }
    }
    //write store state
    auto shopItems = store.limitedItems();
    writer << shopItems.size() << endl;
    for (pair<string,int> item : shopItems){
        writer << item.first << " " << item.second << endl;
    }

    writer.close();
}

void GameManager::loadState(const string& path){
    //string filename = "state.txt";
    ifstream reader(path);
    string line;
    int walikota = 0;
    bool allowNoWalikota = false;

    if(!reader.is_open()){
        throw GMException("Failed to open file! : " + path);
    }

    getline(reader,line);
    int playerCount = stoi(line);
    cout << "Playercount : " << playerCount << endl; //DEBUG
    for (int i = 0; i < playerCount ; i++){
        //iterate per player
        getline(reader,line);
        vector<string> lineholder;
        lineholder = split(line,' ');
        PlayerType ptype = (LCaseToPlayerType[lineholder[1]]);
        Player* player;

        //enforcing single walikota rule && exception for non existent roles :
        if (ptype == 0){
            throw GMException("Invalid player type");
        }
        if (ptype == WALIKOTA){
            if (walikota == 0){
                walikota++;
            }
            else{
                throw GMException("Walikota cannot go over 1");
            }
        }

        cout << "Setup for : " << lineholder[0] << endl; //DEBUG
        //create player
        player = addPlayer(lineholder[0],stoi(lineholder[2]),stoi(lineholder[3]),ptype);

        //populate inventory
        getline(reader,line);
        int itemammt = stoi(line);
        cout << "InventorySize : " << itemammt << endl; //DEBUG
        for (int j = 0; j < itemammt; j++){
            try{
                getline(reader,line);
                player->addToInvEmptySlot(codex.getItemByName(line));
            }
            catch(CodexException){
                throw GMException("Cancel load",line);
            }
        }
        
        //populate field if any
        
        
        if (ptype == PETANI){
            getline(reader,line);
            cout << "Populating field of size : " << line << endl; //DEBUG
            int fieldsize = stoi(line);
            Petani* petani = dynamic_cast<Petani*>(player);
            for (int j = 0; j < fieldsize ; j++){
                getline(reader,line);
                cout << line << endl;
                lineholder = split(line,' ');
                tuple<int,int> location = convertToCoordinate(lineholder[0]);
                Plant* plant = new Plant(codex.getPlantbyName(lineholder[1]));
                plant->setAge(stoi(lineholder[2]));
                petani->setLahan(get<0>(location),get<1>(location),plant);
                }
            //petani->displayGrid();
            }
        else if (ptype == PETERNAK) {
            getline(reader,line);
            cout << "Populating field of size : " << line << endl; //DEBUG
            int fieldsize = stoi(line);
            Peternak* peternak = dynamic_cast<Peternak*>(player);
            for (int j = 0; j < fieldsize ; j++){
                getline(reader,line);
                cout << line << endl;
                lineholder = split(line,' ');
                tuple<int,int> location = convertToCoordinate(lineholder[0]);
                Animal* animal = new Animal(codex.getAnimalbyName(lineholder[1]));
                animal->addWeight(stoi(lineholder[2]));
                peternak->setKandang(get<0>(location),get<1>(location),animal);
            }
            //petani->displayGrid();
        };

    }
    //cekk kalau ada walikot atau belum
    if (!allowNoWalikota && walikota != 1){
        throw GMException("Missing walikota");
    }

    //populate shop
        getline(reader,line);
        cout << "POPULATING SHOP WITH ITEMS : " << line << endl;
        int shopitems = stoi(line);
        for (int i = 0; i < shopitems; i++){
            getline(reader,line);
            vector<string> splitted = split(line,' ');
            cout << splitted[0] << "|" << stoi(splitted[1]) << endl;
            store.addItem(splitted[0],stoi(splitted[1]));
        }

    reader.close();
}