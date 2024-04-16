#include "GeneralStore.hpp"
#include "../utils/StringProcessor.hpp"
#include <string>

using namespace std;

Store::Store() {
    vector<Item*> Items;
    vector<int> Quantity;
    codex = nullptr;
}

Store::Store(vector<string>& ItemList, vector<int>& quantity) {
    this->Items = move(ItemList);
    this->Quantity = quantity;
    cout << "Created Store" << endl;
}

Store::~Store() {} // dtor

int Store::getItemQuantity(const Item* item) const {
    int idx = this->isinStore(item);
    if (idx == -1) {
        return 0;
    }
    else {
        return this->Quantity[idx];
    }
}

int Store::isinStore(const Item* item) const {
    ///cout << "flag isinstore" << endl; // Buat debug saja
    //cout << this->items.size() << endl; // Buat debug saja
    for (int i = 0; i < this->Items.size(); i++) {
        //cout << "flag isinstore loop ke-" << i << endl; // Buat debug saja
        //this->items[i]->displayItem(); // Buat debug saja
        //item->displayItem(); // Buat debug saja
        //cout << "item code in items " << this->items[i]->getItemCode() << endl; // Buat debug saja
        //cout << "item code input " << item->getItemCode() << endl; // Buat debug saja
        if (this->Items[i].compare(item->getItemName()) == 0) {
            //cout << "flag isinstore loop ke-" << i << " finished" << endl; // Buat debug saja
            return i;
        }
        
    }
    return -1;
}

int Store::totalprice(int idx,int quantity){
    int price = codex->getItemReferenceByName(Items[idx-1])->getItemPrice();
    return price * quantity;
}

vector<int> Store::legalSaleList(Player*& player){
    vector<int> retval;
    for (int i = 0; i < Items.size(); i++){
        if (canBuy(player->getType(),codex->getItemReferenceByName(Items[i])->getItemType())){
            retval.push_back(i);
        }
    }
    return retval;
}

void Store::displayStore(const vector<int>& sellList) {
    cout << "Selamat datang di toko!!" << endl << "Beriksut merupakan hal yang dapat Anda Beli" << endl;
    for (int i = 0; i < sellList.size(); i++) {
        cout << i + 1 << ". " << this->Items[sellList[i]] << " - " << this->codex->getItemReferenceByName(Items[sellList[i]])->getItemPrice();
        if (this->Quantity[sellList[i]] != -1) {
            cout << "(" << this->Quantity[sellList[i]] << ")" << endl;
        }
        else {
            cout << endl;
        }
    }
}

void Store::displayStore(){
    cout << "Selamat datang di toko!!" << endl << "Beriksut merupakan hal yang dapat Anda Beli" << endl;
    for (int i = 0; i < this->Items.size(); i++) {
        cout << i + 1 << ". " << this->Items[i] << " - " << this->codex->getItemReferenceByName(Items[i])->getItemPrice();
        if (this->Quantity[i] != -1) {
            cout << "(" << this->Quantity[i] << ")" << endl;
        }
        else {
            cout << endl;
        }
    }
}
bool Store::canBuy(PlayerType Ptype, ItemType Itype){
    return !(Ptype == WALIKOTA && Itype == RECIPE);
}

bool Store::canSell(PlayerType Ptype, ItemType Itype){
    //cout << "PTYPE " << Ptype << " ITYPE " << Itype << endl;
    return !((Ptype == PETANI || Ptype == PETERNAK) && Itype == RECIPE);
}


void Store::addItem(Item*& item, int quantity) {
    int idx = this->isinStore(item);
    if (idx != -1) {
        if (this->Quantity[idx] != -1){this->Quantity[idx] += quantity;}
        
    }
    else {
        this->Items.push_back(item->getItemName());
        this->Quantity.push_back(quantity);
    }
}

void Store::removeItem(int idx,int quantity){
    this->Quantity[idx-1] -= quantity;
}

string Store::sellItem(int idx, int quantity, Player*& buyer) {
    int money = buyer->getGulden();
    PlayerType type = buyer->getType();
    int quan = this->Quantity[idx - 1];
    if (quan < quantity && quan != -1) {
        throw invalid_argument("StockNotEnough");
    }
    else {
        if (this->totalprice(idx,quantity) > money){
            throw invalid_argument("NotEnoughMoney");
        }
        buyer->changeGulden(-totalprice(idx,quantity));
        string sold = this->Items[idx-1];
        if (quan != -1) {
            if (quan == quantity) {
                //delete this->items[idx - 1];
                this->Items.erase(Items.begin() + idx - 1);
                this->Quantity.erase(Quantity.begin() + idx - 1);
            }
            else {
                this->removeItem(idx,quantity);
            }

        }
        return sold;
    }
}



void Store::buyAs(Player*& buyer){
    int idx,quantity,gulden,InvSpace;
    vector<int> legalList = legalSaleList(buyer);
    displayStore(legalList);
    gulden = buyer->getGulden();
    cout << "Uang Anda : " << gulden << endl;
    InvSpace = buyer->getMaxItemInInventory() - buyer->getItemCountInInventory();
    cout << "Slot penyimpanan tersedia: " << InvSpace << endl;
    cout << endl;
    cout << "Barang ingin dibeli : ";
    string line;
    getline(cin, line);
    //verifikasi
    for (char& c : line){
        if (!isdigit(c)){
            throw out_of_range("Invalid index");
        }
    }
    idx = stoi(line);

    if (idx <= 0 || idx > legalList.size()) {
        throw out_of_range("Invalid index");
    }
    //if (!canBuy(buyer->getType(),this->items[idx-1]->getItemType())){throw invalid_argument("CantBuyException");}
    //udah pasti bisa beli

    cout << "Kuantitas : "; cin >> quantity;
    if (InvSpace < quantity){throw invalid_argument("NotEnoughInventorySpace");}
    string sold = sellItem(legalList[idx],quantity,buyer);

    int sisa = buyer->getGulden();
    cout << "Selamat Anda berhasil membeli " << quantity << " " << sold << ". Uang Anda tersisa " << sisa << "gulden." << endl;
    cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;

    buyer->Player::displayGrid();
    vector<tuple<int,int>> spacelist;
    while (quantity > 0){
        cout << "Petak slot: ";
        spacelist.clear();
        string input;
        getline(cin,input);

        if (split(input,',').size() > quantity){
            cout << "Too many spots! try again" << endl;
            continue;
        }

        bool inputcorrect = true;

        for (string s : split(input,',')){
            auto cords = convertToCoordinate(removeSpaces(s));
            if (cords == make_tuple(-1,-1)){
                cout << "Invalid space (" << removeSpaces(s) << ")! try again." << endl;
                inputcorrect = false;
                break;
            }
            else{
                if (buyer->getInventory().getMap()[get<1>(cords)][get<0>(cords)] != nullptr){
                    cout << "Item already exists! (" << s << ")" << endl;
                    inputcorrect = false;
                }
                // check multi inputs of same space
                for (auto insertedcord : spacelist){
                    if (insertedcord == cords){
                        cout << "Slot inputted twice! (" << s << ")" << endl;
                        inputcorrect = false;
                        break;
                    }
                }
                if (!inputcorrect){
                    break;
                }

                spacelist.push_back(cords);
            }
        }

        if (!inputcorrect) {
            continue;
        }
        else{
            for (tuple<int,int> cord : spacelist){
                buyer->getInventory().set(get<0>(cord),get<1>(cord), codex->getItemByName(sold));
                quantity--;
            }
        }

        if (quantity > 0){
            cout << "Anda masih punya " << quantity << " " << sold << endl;
        }

    }
    
    // for (int i = 0; i < quantity; ++i) {
    //     string cord;
    //     char comma;

    //     // Read the number
    //     cin >> cord;

    //     // Check if it's the last input
    //     if (i < quantity-1) {
    //         // Read the comma
    //         std::cin >> comma;
    //         if (comma != ',') {
    //             std::cerr << "Invalid input format." << std::endl;
    //         }
    //     }
    //     tuple<int, int> pos = convertToCoordinate(cord);
    //     int x = get<1>(pos);
    //     int y = get<0>(pos);
    //     Map<Item> inv = buyer->getInventory();
    //     if (x < 0 || x >= buyer->getInvenW() || y < 0 || y >= buyer->getInvenH()){
    //         cout << "Petak tidak valid" << endl;
    //     } else if (inv.getMap()[x][y] != nullptr){
    //         cout << "Petak tidak kosong" << endl;
    //     }else{
    //         buyer->addToInv(sold,x,y);
    //     }
    //}
    cout << sold << " berhasil disimpan dalam penyimpanan!" << endl;


}

void Store::sellAs(Player*& buyer){
    string input;
    cout << "Berikut merupakan penyimpanan Anda" << endl;
    buyer->Player::displayGrid();
    cout << "Silahkan pilih petak yang ingin Anda jual!" << endl;
    cout << "Petak : ";
    getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<std::string> cords;
    std::string cord;
    while (getline(ss, cord, ',')) {
        cord.erase(0, cord.find_first_not_of(" \t\r\n"));
        cord.erase(cord.find_last_not_of(" \t\r\n") + 1);
        cords.push_back(cord);
    }
    int x,y,sellprice;
    vector<tuple<int, int>> posList;
    for (const auto& cord : cords){ // loop buat ngecheck apakah semua petak yang di input tidak kosong
        tuple<int, int> pos = convertToCoordinate(cord);
        x = get<1>(pos);
        y = get<0>(pos);
        Map<Item> inv = buyer->getInventory();
        if (inv.getMap()[x][y] == nullptr){throw invalid_argument("PetakEmpty");}
        else if (!canSell(buyer->getType(),inv.getMap()[x][y]->getItemType())){throw invalid_argument("CantSellException");}
        posList.push_back(pos);
    }
    sellprice = 0;
    for (const auto& pos : posList){
        x = get<1>(pos); 
        y = get<0>(pos);
        Map<Item>& inv = buyer->getInventory();
        Item* items = inv.getMap()[x][y];
        sellprice += items->getItemPrice();
        this->addItem(items,1);
        //buyer->addToInv(nullptr,x,y);
        buyer->getInventory().set(y,x,nullptr);
    }
    cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << sellprice << " gulden!" << endl;
    
}
void Store::openAs(Player*& buyer, Action Aksi){
    if (Aksi == BUY){
        this->buyAs(buyer);
    }else{
        this->sellAs(buyer);
    }
}