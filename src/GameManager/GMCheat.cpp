#include "GameManager.hpp"

//cheat menu, if you will
void GameManager::cheat(){
    awaitMultiInput("What is your command?: ",' ');
    string commands[] = {"VIEW","GIVE","TAKE"};
    string codexpage[] = {"PLANTS","ANIMALS","PRODUCTS","BUILDINGS","SOURCE","PLAYERS"};
    Item* thing; //placeholder for case 0,4
    switch (findIn(lastMultiInput[0],commands,3))
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
        break;
    case 2:
        break;
    default:
        cout << "Cheat "<< lastMultiInput[0] << " doesnt exist!" << endl;
        break;
    }
}
