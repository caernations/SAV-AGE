#include "StringProcessor.hpp"

#include <iostream>
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


std::string convertToReadable(const std::string& str, bool capitalizeFirstWord, bool capitalizeAllWords) {
    std::string result = str;

    // Convert string to lowercase
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    // Replace underscores with spaces
    std::replace(result.begin(), result.end(), '_', ' ');

    // Capitalize first letter of first word if required
    if (capitalizeFirstWord && !result.empty()) {
        result[0] = std::toupper(result[0]);
    }

    // Capitalize all words if required
    if (capitalizeAllWords) {
        bool makeUpper = true;
        for (char& c : result) {
            if (std::isalpha(c)) {
                if (makeUpper) {
                    c = std::toupper(c);
                    makeUpper = false;
                }
            } else {
                makeUpper = true;
            }
        }
    }

    return result;
}

std::tuple<int,int> convertToCoordinate(const std::string& str) {
    // Check if the string is valid
    if (str.empty() || !std::isalpha(str[0]) || !std::isdigit(str[1])) {
        return std::make_tuple(-1, -1);
    }

    // Check if the rest of the string contains any non-digit characters
    for (size_t i = 2; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return std::make_tuple(-1, -1);
        }
    }

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

string coordinateToString(const std::tuple<int,int> coordinate){
    string retval;
    char x = 'A' + get<0>(coordinate);
    string y = to_string(get<1>(coordinate) + 1);
    cout << "DEBUG, Y :" << y << endl;
    retval += x;
    if (get<1>(coordinate) < 10){
        retval += "0";
    }

    retval += y;

    return (retval);
}

int findIn(const string& object, const string source[], const int& size){
    //cout << "FINDING" << endl;
    int retval = -1;
    for (int i = 0; i < size; i++){
        if (source[i].compare(object) == 0){
            //cout << "FOUND AT " << i << endl;
            return i;
        }
        else{
            //cout << object << source[i] << endl;
        }
    }
    //cout << "NOT FOUND !" << endl;
    return retval;
}

//is in
bool isOneOf(const string& input, const vector<string>& comparison){
    for(string item : comparison){
        if (input.compare(item) == 0){
            return true;
        }
    }
    return false;
}

bool lexCompare(const string& a, const string& b){
    return lexicographical_compare(a.begin(),a.end(),b.begin(),b.end());
};

string removeSpaces(const string& x){
    string retval;
    for (char c : x){
        if (c != ' '){
            retval.push_back(c);
        }
    }
    return retval;
}

bool digitOnly(string text){
    for (char& x : text){
        if (x == text[0] && x == '-'){
            continue;
        }
        if (!isdigit(x)){
            return false;
        }
    }
    return true;
}