#ifndef __STRINGPROCESSOR_HPP__
#define __STRINGPROCESSOR_HPP__

#include <vector>
#include <string>
#include <tuple>

using namespace std;

vector<string> split(string input,char splitterchar);

string convertToReadable(const string& str);

tuple<int,int> convertToCoordinate(const string& str);

#endif