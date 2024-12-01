#ifndef __CLOTHING_H__
#define __CLOTHING_H__

#include "products/product.h"
#include <sstream>

class Clothing : public Product {
    std::string size;
    std::string color;
    std::string material;
public:
    Clothing(size_t id, const std::string &name, const std::string &description,
             double price, double weight, const std::string &manufacturer,
             const Dimensions &dimensions, const std::string &size,
             const std::string &color, const std::string &material)
        : Product(id, name, description, price, weight, manufacturer, dimensions),
          size(size), color(color), material(material) {}
    std::string generateDescription() const override {
        std::stringstream ss;
        ss << Product::generateDescription();
        ss << "Size: " << size << '\n';
        ss << "Color: " << color << '\n';
        ss << "Material: " << material << '\n';
        return ss.str();
    }
    std::string getCategory() const override {
        static const std::string category = "Clothing";
        return category;
    }
};

#endif