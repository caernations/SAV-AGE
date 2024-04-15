#include "GameManager.hpp"

//SAVESTATE AND LOADSTATE
void GameManager::saveState(const string& path){
    int playerCount = activePlayers.size();
    string filename = "testsave.txt";
    ofstream writer(path+"/"+filename);
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

    writer.close();
}

void GameManager::loadState(const string& path){
    string filename = "state.txt";
    ifstream reader(path+"/"+filename);
    string line;
    int walikota = 0;

    if(!reader.is_open()){
        throw GMException("Failed to open file! : " + path + "/" + filename);
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
        cout << "InventorySize : " << playerCount << endl; //DEBUG
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
        getline(reader,line);
        cout << "Populating field of size : " << line << endl; //DEBUG
        if (ptype == PETANI){
            int fieldsize = stoi(line);
            Petani* petani = dynamic_cast<Petani*>(player);
            for (int j = 0; j < fieldsize ; j++){
                getline(reader,line);
                lineholder = split(line,' ');
                tuple<int,int> location = convertToCoordinate(lineholder[0]);
                Plant* plant = new Plant(codex.getPlantbyName(lineholder[1]));
                plant->setAge(stoi(lineholder[2]));
                petani->setLahan(get<0>(location),get<1>(location),plant);
                }
            //DEBUG
            cout << "Report item" << endl;
            //petani->displayGrid();
            }
        else if (ptype == PETERNAK) {

        };
        
        activePlayers.push_back(player);
    }

    reader.close();
}