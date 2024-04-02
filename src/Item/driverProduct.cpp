#include "Product.hpp"
#include <iostream>
#include <memory>

int main() {
    // Create an Product object (prod1)
    std::unique_ptr<Product> prod1(new Product(1, "PRODUCT_MATERIAL_PLANT", "TEAK_TREE", 0, "TAW", "TEAK_WOOD", 9));
    std::unique_ptr<Product> prod2(new Product(11,"PRODUCT_ANIMAL", "HORSE" ,8, "HRM", "HORSE_MEAT", 10));
    
    std::cout << "prod1:" << std::endl;
    std::cout << "Product ID: " << prod1->getProductID() << std::endl;
    std::cout << "Product Type: " << prod1->getProductType() << std::endl;
    std::cout << "Origin: " << prod1->getOrigin() << std::endl;
    std::cout << "Added Weight: " << prod1->getAddedWeight() << std::endl;
    std::cout << "Consumable: " << (prod1->isProductConsumable() ? "Yes" : "No") << std::endl;

    std::cout << "prod2:" << std::endl;
    std::cout << "Product ID: " << prod2->getProductID() << std::endl;
    std::cout << "Product Type: " << prod2->getProductType() << std::endl;
    std::cout << "Origin: " << prod2->getOrigin() << std::endl;
    std::cout << "Added Weight: " << prod2->getAddedWeight() << std::endl;
    std::cout << "Consumable: " << (prod2->isProductConsumable() ? "Yes" : "No") << std::endl;

    return 0;
}


// HOW TO RUN
// g++ -o driverProduct Item.cpp Product.cpp driverProduct.cpp
// ./driverProduct
