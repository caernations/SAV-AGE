#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <exception>
using namespace std;

struct InventoryEmptyException : public exception {
    const char* what() const throw() {
        return "Inventory kosong";
    }
};

struct InventoryFullException : public exception {
    const char* what() const throw() {
        return "Inventory penuh";
    }
};

struct LahanFullException : public exception {
    const char* what() const throw() {
        return "Lahan penuh";
    }
};

struct NoPlantInInventoryException : public exception {
    const char* what() const throw() {
        return "Tidak ada tumbuhan di inventory";
    }
};

struct NoPlantToHarvestException : public exception {
    const char* what() const throw() {
        return "Tidak ada tumbuhan yang bisa dipanen";
    }
};

struct NotAbleToBuildException : public exception {
    const char* what() const throw() {
        return "Tidak bisa membangun";
    }
};

struct NoFoodInInventoryException : public exception {
    const char* what() const throw() {
        return "Tidak ada makanan di inventory";
    }
};

#endif