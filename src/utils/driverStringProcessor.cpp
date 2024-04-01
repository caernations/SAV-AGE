#include "StringProcessor.hpp"
#include "StringProcessor.cpp"
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

    string input = "TEAK_WOOD";
    string output = convertToReadable(input);
    cout << output << std::endl;

    string input2 = "A02";
    tuple<int,int> output2 = convertToCoordinate(input2);
    cout << "Column : " << get<0>(output2) << endl;
    cout << "Row : " << get<1>(output2) << endl;

    return 0;
}