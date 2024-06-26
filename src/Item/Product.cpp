#include "Product.hpp"

Product::Product() : Item(0, "", "", 0,PRODUCT), productID(0), productType(), origin(""), added_weigth(0) {}

Product::Product(int productID,ProductType productType,std::string origin,int added_weigth,const std::string& itemCode, const std::string& itemName, double itemPrice) : Item(0, itemCode, itemName, itemPrice, PRODUCT), productID(productID), productType(productType),origin(origin), added_weigth(added_weigth) {}

Product::~Product() {}

int Product::getProductID() const {
    return productID;
}

ProductType Product::getProductType() const {
    return productType;
}

std::string Product::getOrigin() const {
    return origin;
}

void Product::setProductID(int newproductID) {
    productID = newproductID;
}

string Product::convertProductTypeToString(ProductType productType) const {
    switch (productType) {
        case PRODUCT_FRUIT_PLANT:
            return "PRODUCT_FRUIT_PLANT";
        case PRODUCT_ANIMAL:
            return "PRODUCT_ANIMAL";
        case PRODUCT_MATERIAL_PLANT:
            return "PRODUCT_MATERIAL_PLANT";
        default:
            return "";
    }
}

void Product::setProductType(const ProductType& newproductType) {
    productType = newproductType;
}

void Product::setOrigin(const std::string& neworigin){
    origin = neworigin;
}

void Product::setAddedWeigth(int newAddedWeigth) {
    added_weigth = newAddedWeigth;
}

bool Product::operator==(const Product& other) const {
    return productID == other.productID;
}

Product& Product::operator=(const Product& other) {
    productID = other.productID;
    productType = other.productType;
    origin = other.origin;
    added_weigth = other.added_weigth;
    return *this;
}

void Product::displayItem() const {
    std::cout << "product ID: " << productID << ", Type: " << productType << ", Origin: " << origin << ", Added Weight: " << added_weigth << std::endl;
}

Item* Product::cloneItem() const {
    return new Product(*this);
}

bool Product::isProductConsumable() const {
    return added_weigth > 0;
}

bool Product::isMaterial() const {
    return productType == PRODUCT_MATERIAL_PLANT;
}



