#include "StringProcessor.hpp"
#include "StringProcessor.cpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
    string test[] = {"1","2","3","10","11"};

    cout << findIn("balls",test,5) << endl;

    return 0;
}