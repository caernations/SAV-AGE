#include "StringProcessor.hpp"
#include <iostream>

using namespace std;

int main(){
    string test = "10,2,3,10";
    cout << "String :" << test << endl;
    cout << "Splitting..." << endl;

    vector<string> spleet = split(test,',');

    cout << "Split result :" << endl;

    for (string item: spleet){
        cout << item << endl;
    }

    return 0;
}