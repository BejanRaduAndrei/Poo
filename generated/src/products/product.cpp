#include <products/product.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <products/productFactory.h>

Product::Product(size_t id, const std::string &name, size_t price)
{
	this->id = id;
	this->name = name;
	this->price = price;
}

Product::Product(size_t id, const std::string &name,
		 const std::string &description,
		 double price, double weight, const std::string &manufacturer,
		 const Dimensions &dimensions)
{
	this->id = id;
	this->name = name;
	this->description = description;
	this->price = price;
	this->weight = weight;
	this->manufacturer = manufacturer;
	this->dimensions = dimensions;
}

std::string Product::generateDescription() const
{
	std::stringstream ss;
	ss << "ID: " << id << '\n'
	   << "Name: " << name << '\n'
	   << "Description: ";
	ss << description << '\n';
	ss << "Category: " << getCategory() << '\n';
	ss << "Price: " << price << '\n';
	if (weight != 0) {
		ss << "Weight: " << weight << '\n';
	}
	if (manufacturer != "") {
		ss << "Manufacturer: " << manufacturer << '\n';
	}
	if (dimensions.length != 0.0 && dimensions.width != 0.0 &&
	    dimensions.width != 0) {
		ss << "Dimensions: " << dimensions.length << 'x'
		   << dimensions.width << 'x' << dimensions.height << '\n';
	}
	return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Product &obj)
{
	os << obj.generateDescription();
	return os;
}

std::vector<std::shared_ptr<Product>> Product::readProductsFromInput(std::istream& ss)
{
	std::vector<std::shared_ptr<Product>> products;
	std::string line;

	while (std::getline(ss, line)) {
		std::istringstream iss(line);
		size_t id;
		std::string name, description, categoryStr, manufacturer;
		double price, weight;
		Dimensions dimensions;
		ProductFactory *factory = ProductFactory::getInstance();

		// Assuming the file format is: id,name,description,category,price,weight,manufacturer,length,width,height
		// if the category is not unknown, read 3 more fields
		// and create a product of the corresponding type
		std::string idStr, priceStr, weightStr, lengthStr, widthStr,
			heightStr;

		if (!std::getline(iss, idStr, ',') ||
		    !std::getline(iss, name, ',') ||
		    !std::getline(iss, description, ',') ||
		    !std::getline(iss, categoryStr, ',') ||
		    !std::getline(iss, priceStr, ',') ||
		    !std::getline(iss, weightStr, ',') ||
		    !std::getline(iss, manufacturer, ',') ||
		    !std::getline(iss, lengthStr, ',') ||
		    !std::getline(iss, widthStr, ',') ||
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
		} catch (const std::invalid_argument &e) {
			continue;
		}

		if (categoryStr != "unknown") {
			std::string extra1, extra2, extra3;
			if (!std::getline(iss, extra1, ',') ||
			    !std::getline(iss, extra2, ',') ||
			    !std::getline(iss, extra3, ',')) {
				// Handle error
				continue;
			}
			products.emplace_back(factory->createProduct(
				categoryStr, id, name, description, price,
				weight, manufacturer, dimensions, extra1,
				extra2, extra3));

			
		} else {
			products.emplace_back(factory->createProduct(id, name, description, price,
					      weight, manufacturer, dimensions));
		}
	}

	return products;
}
