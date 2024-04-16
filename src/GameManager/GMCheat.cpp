#include "GameManager.hpp"
#include <algorithm>

using namespace std;
//cheat menu, if you will
void GameManager::cheat(){
    awaitMultiInput("What is your command?: ",' ');
    string commands[] = {"INSIGHT","CONJURE","GIVE","DESTROY","CHRONOS","GREED","MASS"};
    string codexpage[] = {"PLANTS","ANIMALS","PRODUCTS","BUILDINGS","SOURCE","PLAYERS"};
    Item* thing; //placeholder for case 0,4
    tuple<int,int> pos;
    int x;
    int i = 0;

    if (lastMultiInput.size() <= 1){
        throw GMException("Incorrect cheat command size", "Size : " + to_string(lastMultiInput.size()));
    }

    switch (findIn(lastMultiInput[0],commands,7))
    {
    case 0:
        switch (findIn(lastMultiInput[1],codexpage,6)){
            case 0:
                codex.showPlants();
                break;
            case 1:
                codex.showAnimals();
                break;
            case 2:
                codex.showProducts();
                break;
            case 3:
                codex.showBuildings();
                break;
            case 4:
                thing = codex.getSource(codex.getProduct(lastMultiInput[2]));
                if (thing != nullptr){
                    thing->displayItem();
                }
                else{
                    cout << "Invalid item or Product does not exist" << endl;
                }
                break;
            case 5:
                for (Player*& item : activePlayers){
                    cout << item->getPlayerName() << " : " << PlayerTypeToString[item->getType()] << endl;
                }
                break;
            default:
                cout << "Table does not exist!" << endl;
                break;
        }

        break;
    case 1:
        thing = codex.getItemByName(lastMultiInput[1]);
        pos = convertToCoordinate(lastMultiInput[2]);
        if (thing == nullptr){
            cout << "Item does not exist!" << endl;
        }
        else{
            activePlayers[turn]->getInventory().set(get<0>(pos),get<1>(pos),thing);
            activePlayers[turn]->updateItemCount();
            cout << "Conjured " << convertToReadable(thing->getItemName(),true, false) << " at " << coordinateToString(pos) << endl;
        }
        break;
    case 2:
        thing = codex.getItemByName(lastMultiInput[1]);
        x = min(stoi(lastMultiInput[2]),activePlayers[turn]->getInventory().remainingSlots());
        if (thing == nullptr){
            cout << "Item does not exist!" << endl;
        }
        else if (x == 0){
            cout << "No space remaining!" << endl;
        }
        else{
            for (i = 0; i < x; i++){
                activePlayers[turn]->addToInvEmptySlot(thing);
            }
        }
        break;
    case 3:
        pos = convertToCoordinate(lastMultiInput[1]);
        if (activePlayers[turn]->getInventory().getMap()[get<1>(pos)][get<0>(pos)] == nullptr){
            cout << "Cannot destroy null!" << endl;
        }
        else{
            cout << "Destroyed " << convertToReadable(activePlayers[turn]->getInventory().getMap()[get<1>(pos)][get<0>(pos)]->getItemName(),true, false) << " at " << coordinateToString(pos) << endl;
            activePlayers[turn]->getInventory().set(get<0>(pos),get<1>(pos),nullptr);
            activePlayers[turn]->updateItemCount();
        }
        break;
    case 4:
        x = stoi(lastMultiInput[1]);
        nextTick(x);
        cout << "Skipping time by " << x << " ticks";
        break;
    case 5: //GREED
        if (digitOnly(lastMultiInput[1])){
            int x = stoi(lastMultiInput[1]);

            if (x + activePlayers[turn]->getGulden() < 0){
                cout << "Cannot lose gold more than" << activePlayers[turn]->getGulden() <<"!" << endl;
            }

            activePlayers[turn]->changeGulden(x);
            if (x > 0){
                cout << "Gained gold by " << x << "!" << endl;
            }
            else{
                cout << "Lost " << x << " gold!" << endl;
            }
        }
        break;    
    case 6: //MASS
        if (digitOnly(lastMultiInput[1])){
            int x = stoi(lastMultiInput[1]);

            if (x + activePlayers[turn]->getBeratBadan() < 0){
                cout << "Cannot lose weight more than" << activePlayers[turn]->getBeratBadan() <<"!" << endl;
            }

            activePlayers[turn]->changeBeratBadan(x);
            if (x > 0){
                cout << "Gained weight by " << x << "!" << endl;
            }
            else{
                cout << "Lost " << x << " weight!" << endl;
            }
        }
        break;
    default:
        cout << "Cheat "<< lastMultiInput[0] << " doesnt exist!" << endl;
        break;
    }
    
}
