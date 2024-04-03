#include "Codex.hpp"
#include <iostream>

int main(){

    cout << "START" << endl;

    Codex test;

    cout << "READING" << endl;

    test.populatecodex("../config");

    cout << "DONE" << endl;
}