#include "StringProcessor.hpp"

#include <iostream>
#include <algorithm>
#include <string>

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

std::string convertToReadable(const std::string& str) {
    std::string result = str;
    
    // Convert string to lowercase
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    // Replace underscores with spaces
    std::replace(result.begin(), result.end(), '_', ' ');

    return result;
};

std::tuple<int,int> convertToCoordinate(const std::string& str) {
    // Convert the string to uppercase
    std::string uppercaseStr = str;
    std::transform(uppercaseStr.begin(), uppercaseStr.end(), uppercaseStr.begin(), ::toupper);

    // Extract the column letter and row number
    char columnLetter = uppercaseStr[0];
    int rowNumber = std::stoi(uppercaseStr.substr(1)) - 1;

    // Convert the column letter to a numerical index
    int columnIndex = columnLetter - 'A';

    return std::make_tuple(columnIndex, rowNumber);
};