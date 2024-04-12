#ifndef __STRINGPROCESSOR_HPP__
#define __STRINGPROCESSOR_HPP__

#include <vector>
#include <string>
#include <tuple>

using namespace std;

vector<string> split(string input,char splitterchar);

string convertToReadable(const string& str, bool capitalizeFirstWord, bool capitalizeAllWords);

tuple<int,int> convertToCoordinate(const string& str);

int findIn(const string& object, const string source[], const int& size);

#endif