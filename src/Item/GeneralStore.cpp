#include "GeneralStore.hpp"

Store::Store() {
    vector<Item*> item;
    vector<int> quantity;
    this->items = move(item);
    this->Quantity = quantity;
}

Store::Store(vector<Item*> ItemList, vector<int>& quantity) {
    this->items = move(ItemList);
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
    cout << "flag isinstore" << endl;
    cout << this->items.size() << endl;
    for (int i = 0; i < this->items.size(); i++) {
        cout << "flag isinstore loop ke-" << i << endl;
        this->items[i]->displayItem();
        item->displayItem();
        cout << "item code in items " << this->items[i]->getItemCode() << endl;
        cout << "item code input " << item->getItemCode() << endl;
        if (this->items[i]->getItemCode() == item->getItemCode()) {
            cout << "flag isinstore loop ke-" << i << " finished" << endl;
            return i;
        }
        
    }
    return -1;
}

void Store::displayStore() {
    cout << "Selamat datang di toko!!" << endl << "Berikut merupakan hal yang dapat Anda Beli" << endl;
    for (int i = 0; i < this->items.size(); i++) {
        cout << i + 1 << ". " << this->items[i]->getItemName() << " - " << this->items[i]->getItemPrice();
        if (this->Quantity[i] != -1) {
            cout << "(" << this->Quantity[i] << ")" << endl;
        }
        else {
            cout << endl;
        }
    }
}

void Store::addItem(Item* item, int quantity) {
    int idx = this->isinStore(item);
    if (idx != -1) {
        if (this->Quantity[idx] != -1){this->Quantity[idx] += quantity;}
        
    }
    else {
        this->items.push_back(move(item));
        this->Quantity.push_back(quantity);
    }
}

Item* Store::sellItem(int idx, int quantity) {
    if (idx <= 0 || idx > this->Quantity.size()) {
        throw out_of_range("Invalid index");
    }
    int quan = this->Quantity[idx - 1];
    if (quan < quantity && quan != -1) {
        throw invalid_argument("StockNotEnough");
    }
    else {
        Item* sold = this->items[idx-1];
        if (quan != -1) {
            int x = quan - quantity;
            if (x == 0) {
                delete this->items[idx - 1];
                this->items.erase(items.begin() + idx - 1);
                this->Quantity.erase(Quantity.begin() + idx - 1);
            }
            else {
                this->Quantity[idx - 1] = x;
            }

        }
        return sold;
    }
}
