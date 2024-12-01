#ifndef __FURNITURE_H__
#define __FURNITURE_H__

#include "products/product.h"
#include <sstream>

class Furniture : public Product {
    std::string material;
    std::string color;
    std::string style;
public:
    Furniture(size_t id, const std::string &name, const std::string &description,
              double price, double weight, const std::string &manufacturer,
              const Dimensions &dimensions, const std::string &material,
              const std::string &color, const std::string &style)
        : Product(id, name, description, price, weight, manufacturer, dimensions),
          material(material), color(color), style(style) {}
    std::string generateDescription() const override {
        std::stringstream ss;
        ss << Product::generateDescription();
        ss << "Material: " << material << '\n';
        ss << "Color: " << color << '\n';
        ss << "Style: " << style << '\n';
        return ss.str();
    }
    std::string getCategory() const override {
        static const std::string category = "Furniture";
        return category;
    }
};

#endif