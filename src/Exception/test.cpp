#include "Ex.hpp"
#include <iostream>
using namespace std;

int main() {
    tes t;
    try {
        //fungsi yang akan melempar exception
    } catch (GameException& e) {
        cout << e.what() << endl;
    }
}

