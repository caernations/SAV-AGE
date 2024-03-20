#include "Color.hpp"

int main() {
    Color colorPrinter;

    colorPrinter.colorBlue("Blue text\n");
    colorPrinter.colorRed("Red text\n");
    colorPrinter.colorGreen("Green text\n");
    colorPrinter.colorYellow("Yellow text\n");

    return 0;
}

// HOW TO RUN
// g++ -o driverColor Color.cpp driverColor.cpp
// ./driverColor