#ifndef __STRINGPROCESSOR_HPP__
#define __STRINGPROCESSOR_HPP__

#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

vector<string> split(string input,char splitterchar);

string convertToReadable(const string& str, bool capitalizeFirstWord, bool capitalizeAllWords);

tuple<int,int> convertToCoordinate(const string& str);

string coordinateToString(const std::tuple<int,int> coordinate);

int findIn(const string& object, const string source[], const int& size);

bool isOneOf(const string& input, const vector<string>& comparison);

//returns true when A < B
bool lexCompare(const string& a, const string& b);

string removeSpaces(const string& x);



#endif