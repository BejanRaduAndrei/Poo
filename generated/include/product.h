#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
#include <tuple>
#include <vector>

#include <category.h>

struct Dimensions {
    float length;
    float width;
    float height;
};

class Product {
  size_t id;
  std::string name;
  std::string description;
  Category category;
  double price;
  double weight;
  std::string manufacturer;
  Dimensions dimensions;

public:
  Product(size_t, const std::string &);
  // Expected to be called when reading all the data about products
  // from a file or database
  Product(size_t, const std::string &, const std::string &, Category &,
          double, double, const std::string &, const Dimensions &);
  size_t getID() const;
  const std::string &getName() const;
  const std::string &getDescription() const;
  const Category &getCategory() const;
  double getPrice() const;
  double getWeight() const;
  const std::string &getManufacturer() const;
  const Dimensions &getDimensions() const;
  void setName(const std::string &);
  void setDescription(const std::string &);
  void setPrice(const double);
  void setWeight(const double);
  friend std::ostream& operator<<(std::ostream& os, const Product& obj);
  static std::vector<Product> readProductsFromFile(const std::string &filename);
  static std::vector<Product> readProductsFromStdin();
};

#endif