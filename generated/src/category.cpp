#include <iostream>
#include <category.h>

const std::string& categoryToString(Category category) {
    static const std::string electronics = "Electronics";
    static const std::string clothings = "Clothings";
    static const std::string books = "Books";
    static const std::string toys = "Toys";
    static const std::string groceries = "Groceries";
    static const std::string furnitures = "Furnitures";
    static const std::string sports = "Sports";
    static const std::string automotives = "Automotives";
    static const std::string unknown = "Unknown";

    switch(category) {
        case ELECTRONICS: return electronics;
        case CLOTHINGS: return clothings;
        case BOOKS: return books;
        case TOYS: return toys;
        case GROCERIES: return groceries;
        case FURNITURES: return furnitures;
        case SPORTS: return sports;
        case AUTOMOTIVES: return automotives;
        default: return unknown;
    }
}
Category stringToCategory(const std::string& categoryStr) {
    if (categoryStr == "Electronics") return ELECTRONICS;
    if (categoryStr == "Clothing") return CLOTHINGS;
    if (categoryStr == "Books") return BOOKS;
    if (categoryStr == "Toys") return TOYS;
    if (categoryStr == "Groceries") return GROCERIES;
    if (categoryStr == "Furniture") return FURNITURES;
    if (categoryStr == "Sports") return SPORTS;
    if (categoryStr == "Automotive") return AUTOMOTIVES;
    return UNKNOWN;
}

std::ostream& operator<<(std::ostream& os, const Category& c) {
    os << categoryToString(c);
    return os;
}
