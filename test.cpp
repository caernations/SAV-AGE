#include <iostream>
#include <vector>
#include <string>

int main() {
    // Membuat vector untuk menyimpan nama
    std::vector<std::string> names;

    // Menambahkan nama ke dalam vector
    names.push_back("John");
    names.push_back("Alice");
    names.push_back("Bob");
    names.push_back("Charlie");

    // Mengurutkan nama secara leksikografis dengan iterasi
    for (int i = 0; i < names.size(); ++i) {
        for (int j = i + 1; j < names.size(); ++j) {
            if (names[i] > names[j]) {
                std::cout << names[i] << " > " << names[j] << std::endl;
                std::string temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }
        }
    }

    // Menampilkan nama yang sudah diurutkan
    std::cout << "Nama yang diurutkan secara leksikografis:\n";
    for(const auto& name : names) {
        std::cout << name << std::endl;
    }

    return 0;
}
