#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <string>
using namespace std;

class GameException {
    public:
        virtual const char* what() const throw() = 0;
};

class InventoryEmptyException : public GameException {
    const char* what() const throw() {
        return "Inventory kosong";
    }
};

class InventoryFullException : public GameException {
    const char* what() const throw() {
        return "Inventory penuh";
    }
};

struct IllegalWeightChange : public GameException {
    const char* what() const throw() {
        return "Berat badan tidak bisa dibawah 0!";
    }
};

struct IllegalGoldChange : public GameException {
    const char* what() const throw() {
        return "Uang tidak bisa dibawah 0!";
    }
};

class LahanFullException : public GameException {
    const char* what() const throw() {
        return "Lahan penuh";
    }
};

class NoPlantInInventoryException : public GameException {
    const char* what() const throw() {
        return "Tidak ada tumbuhan di inventory";
    }
};

class NoPlantToHarvestException : public GameException {
    const char* what() const throw() {
        return "Tidak ada tumbuhan yang bisa dipanen";
    }
};

class NotAbleToBuildException : public GameException {
    const char* what() const throw() {
        return "Tidak bisa membangun";
    }
};

class NoFoodInInventoryException : public GameException {
    const char* what() const throw() {
        return "Tidak ada makanan di inventory";
    }
};

class KandangFullException : public GameException {
    const char* what() const throw() {
        return "Kandang penuh";
    }
};

class NoAnimalInInventoryException : public GameException {
    const char* what() const throw() {
        return "Tidak ada hewan di inventory";
    }
};

class NoAnimalToHarvestException : public GameException {
    const char* what() const throw() {
        return "Tidak ada hewan yang bisa dipanen";
    }
};

class KandangKosongException : public GameException {
    const char* what() const throw() {
        return "Kandang kosong";
    }
};

class NotEnoughGuldenException : public GameException {
    const char* what() const throw() {
        return "Gulden tidak cukup";
    }
};

class StringProcessorException : public GameException {
    public:
        string message;

        StringProcessorException(string message){
            this->message = message;
        }

        const char* what() const throw() {
            return "Generic String Processor Exception!";
        }
};

#endif