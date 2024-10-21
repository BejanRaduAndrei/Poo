#include <product.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <category.h>

Product::Product(size_t id, const std::string &name) {
  this->id = id;
  this->name = name;
  this->category = UNKNOWN;
}

Product::Product(size_t id, const std::string &name,
                 const std::string &description, Category &category,
                 double price, double weight, const std::string &manufacturer,
                 const Dimensions &dimensions) {
  this->id = id;
  this->name = name;
  this->description = description;
  this->category = category;
  this->price = price;
  this->weight = weight;
  this->manufacturer = manufacturer;
  this->dimensions = dimensions;
}

size_t Product::getID() const { return this->id; }

const std::string &Product::getName() const { return this->name; }
const std::string &Product::getDescription() const { return this->description; }
const Category &Product::getCategory() const { return this->category; }
double Product::getPrice() const { return this->price; }
double Product::getWeight() const { return this->weight; }
const std::string &Product::getManufacturer() const { return this->manufacturer; }
const Dimensions &Product::getDimensions() const { return this->dimensions; }
void Product::setDescription(const std::string &description) {
  this->description = description;
}
void Product::setPrice(const double price) { this->price = price; }
void Product::setWeight(const double weight) { this->weight = weight; }

std::ostream& operator<<(std::ostream& os, const Product& obj) {
  os << "ID: " << obj.getID() << '\n' << "Name: " << obj.getName() << '\n' << "Description: ";
  os << obj.getDescription() << '\n' << "Category: " << obj.getCategory() << '\n';
  os << "Price: " << obj.getPrice() << '\n';
  if (obj.getWeight() != 0) {
    os << "Weight: " << obj.getWeight() << '\n';
  }
  if(obj.getManufacturer() != "") {
    os << "Manufacturer: " << obj.getManufacturer() << '\n';
  }
  const auto dims = obj.getDimensions();
  if(dims.length != 0.0 && dims.width != 0.0 && dims.width != 0) {
    os << "Dimensions: " << dims.length << 'x' << dims.width << 'x' << dims.height << '\n';
  }
  return os;
}

std::vector<Product> Product::readProductsFromFile(const std::string &filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        size_t id;
        std::string name, description, categoryStr, manufacturer;
        Category category;
        double price, weight;
        Dimensions dimensions;

        // Assuming the file format is: id,name,description,category,price,weight,manufacturer,length,width,height
        std::string idStr, priceStr, weightStr, lengthStr, widthStr, heightStr;

        if (!std::getline(iss, idStr, ',') || !std::getline(iss, name, ',') || !std::getline(iss, description, ',') ||
            !std::getline(iss, categoryStr, ',') || !std::getline(iss, priceStr, ',') || !std::getline(iss, weightStr, ',') ||
            !std::getline(iss, manufacturer, ',') || !std::getline(iss, lengthStr, ',') || !std::getline(iss, widthStr, ',') ||
            !std::getline(iss, heightStr, ',')) {
            // Handle error
            continue;
        }

        try {
            id = std::stoull(idStr);
            price = std::stod(priceStr);
            weight = std::stod(weightStr);
            dimensions.length = std::stod(lengthStr);
            dimensions.width = std::stod(widthStr);
            dimensions.height = std::stod(heightStr);
        } catch (const std::invalid_argument& e) {
            std::cout << "GRIM" << '\n';
            continue;
        }

        category = stringToCategory(categoryStr);
        products.emplace_back(id, name, description, category, price, weight, manufacturer, dimensions);
    }

    return products;
}

std::vector<Product> Product::readProductsFromStdin() {
    std::vector<Product> products;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        size_t id;
        std::string name, description, categoryStr, manufacturer;
        Category category;
        double price, weight;
        Dimensions dimensions;

        // Assuming the file format is: id,name,description,category,price,weight,manufacturer,length,width,height
        std::string idStr, priceStr, weightStr, lengthStr, widthStr, heightStr;

        if (!std::getline(iss, idStr, ',') || !std::getline(iss, name, ',') || !std::getline(iss, description, ',') ||
            !std::getline(iss, categoryStr, ',') || !std::getline(iss, priceStr, ',') || !std::getline(iss, weightStr, ',') ||
            !std::getline(iss, manufacturer, ',') || !std::getline(iss, lengthStr, ',') || !std::getline(iss, widthStr, ',') ||
            !std::getline(iss, heightStr, ',')) {
            // Handle error
            continue;
        }

        try {
            id = std::stoull(idStr);
            price = std::stod(priceStr);
            weight = std::stod(weightStr);
            dimensions.length = std::stod(lengthStr);
            dimensions.width = std::stod(widthStr);
            dimensions.height = std::stod(heightStr);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid argument" << '\n';
            continue;
        }

        category = stringToCategory(categoryStr);
        products.emplace_back(id, name, description, category, price, weight, manufacturer, dimensions);
    }

    return products;
}