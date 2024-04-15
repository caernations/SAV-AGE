#include "GameManager.hpp"
#include <algorithm>

using namespace std;
//cheat menu, if you will
void GameManager::cheat(){
    awaitMultiInput("What is your command?: ",' ');
    string commands[] = {"INSIGHT","CONJURE","GIVE","DESTROY","CHRONOS"};
    string codexpage[] = {"PLANTS","ANIMALS","PRODUCTS","BUILDINGS","SOURCE","PLAYERS"};
    Item* thing; //placeholder for case 0,4
    tuple<int,int> pos;
    int x;
    int i = 0;
    switch (findIn(lastMultiInput[0],commands,5))
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
            activePlayers[turn]->addToInv(thing,get<0>(pos),get<1>(pos));
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
        }
        break;
    case 4:
        x = stoi(lastMultiInput[1]);
        nextTick(x);
        cout << "Skipping time by " << x << " ticks";
        break;
    default:
        cout << "Cheat "<< lastMultiInput[0] << " doesnt exist!" << endl;
        break;
    }
}
