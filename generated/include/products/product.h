#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
#include <tuple>
#include <vector>
#include <memory>

struct Dimensions {
	float length;
	float width;
	float height;
};

class Product {
	size_t id;
	std::string name;
	std::string description;
	double price;
	double weight;
	std::string manufacturer;
	Dimensions dimensions;

    public:
	Product(size_t, const std::string &, size_t);
	// Expected to be called when reading all the data about products
	// from a file or database
	Product(size_t, const std::string &, const std::string &, double,
		double, const std::string &, const Dimensions &);
	const size_t getID() const
	{
		return id;
	}
	const double getPrice() const
	{
		return price;
	}
	virtual std::string generateDescription() const;
	friend std::ostream &operator<<(std::ostream &os, const Product &obj);
	static std::vector<std::shared_ptr<Product> >
	readProductsFromInput(std::istream &ss);
	virtual std::string getCategory() const
	{
		return "Unknown";
	}
};

#endif