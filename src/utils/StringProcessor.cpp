#include "StringProcessor.hpp"

#include <iostream>

vector<string> split(string input,char splittingchar){
    string::iterator iterator = input.begin();
    string::iterator end = input.end();

    vector<string> retval;
    while(iterator != end){
        string temp;
        while(*iterator != splittingchar && iterator != end){
            temp.push_back(*iterator);
            iterator++;
        }
        if (!temp.empty()){
            retval.push_back(temp);
            temp.clear();
        };

        if(iterator != end){
            iterator++;
        }
    }
    return retval;
};