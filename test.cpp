#include <iostream>
#include <cctype> // For tolower function
#include <string>

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;

    // Convert each character to lowercase
    for (char& c : input) {
        c = std::tolower(c);
    }

    std::cout << "Lowercase string: " << input << std::endl;

    return 0;
}
