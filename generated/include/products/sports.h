#ifndef __SPORTS_H__
#define __SPORTS_H__

#include "products/product.h"
#include <sstream>

class Sports : public Product {
    std::string sportType;
    std::string brand;
    std::string model;

public:
    Sports(size_t id, const std::string &name, const std::string &description,
            double price, double weight, const std::string &manufacturer,
            const Dimensions &dimensions, const std::string &sportType,
            const std::string &brand, const std::string &model)
        : Product(id, name, description, price, weight, manufacturer, dimensions),
          sportType(sportType), brand(brand), model(model) {}
    std::string generateDescription() const override {
        std::stringstream ss;
        ss << Product::generateDescription();
        ss << "Sport Type: " << sportType << '\n';
        ss << "Brand: " << brand << '\n';
        ss << "Model: " << model << '\n';
        return ss.str();
    }
    std::string getCategory() const override {
        static const std::string category = "Sports";
        return category;
    }
};


#endif