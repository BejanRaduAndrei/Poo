#ifndef __ELECTRONICS_H__
#define __ELECTRONICS_H__

#include "products/product.h"
#include <sstream>

class Electronics: public Product {
    std::string brand;
    std::string model;
    std::string serialNumber;

public:
    Electronics(size_t id, const std::string &name, const std::string &description,
                double price, double weight, const std::string &manufacturer,
                const Dimensions &dimensions, const std::string &brand,
                const std::string &model, const std::string &serialNumber)
        : Product(id, name, description, price, weight, manufacturer, dimensions),
          brand(brand), model(model), serialNumber(serialNumber) {}
    std::string generateDescription() const override {
        std::stringstream ss;
        ss << Product::generateDescription();
        ss << "Brand: " << brand << '\n';
        ss << "Model: " << model << '\n';
        ss << "Serial Number: " << serialNumber << '\n';
        return ss.str();
    }
    std::string getCategory() const override {
        static const std::string category = "Electronics";
        return category;
    }
    const std::string& getBrand() const {
        return brand;
    }
};

#endif