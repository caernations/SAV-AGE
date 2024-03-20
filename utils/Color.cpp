#include "Color.hpp"

void Color::colorBlue(string text) {
    cout << "\033[1;34m" << text << "\033[0m";
}

void Color::colorRed(string text) {
    cout << "\033[1;31m" << text << "\033[0m";
}

void Color::colorGreen(string text) {
    cout << "\033[1;32m" << text << "\033[0m";
}

void Color::colorYellow(string text) {
    cout << "\033[1;33m" << text << "\033[0m";
}