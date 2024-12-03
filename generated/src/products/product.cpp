#include <products/product.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <products/productFactory.h>

// Constructor: Initializes a product with minimal attributes.
Product::Product(size_t id, const std::string &name, size_t price)
{
	this->id = id;
	this->name = name;
	this->price = price;
}

// Constructor: Initializes a product with detailed attributes.
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

// Generates a formatted string description of the product.
std::string Product::generateDescription() const
{
	std::stringstream ss;
	ss << "ID: " << id << '\n'
	   << "Name: " << name << '\n'
	   << "Description: ";
	ss << description << '\n';
	ss << "Category: " << getCategory() << '\n'; // Calls subclass-specific logic for category.
	ss << "Price: " << price << '\n';
	if (weight != 0) { // Includes weight only if it's non-zero.
		ss << "Weight: " << weight << '\n';
	}
	if (manufacturer != "") { // Includes manufacturer if it exists.
		ss << "Manufacturer: " << manufacturer << '\n';
	}
	if (dimensions.length != 0.0 && dimensions.width != 0.0 &&
	    dimensions.width != 0) { // Includes dimensions if valid.
		ss << "Dimensions: " << dimensions.length << 'x'
		   << dimensions.width << 'x' << dimensions.height << '\n';
	}
	return ss.str();
}

// Overloads the << operator to print the product description.
std::ostream &operator<<(std::ostream &os, const Product &obj)
{
	os << obj.generateDescription();
	return os;
}

// Reads products from an input stream and creates a vector of Product objects.
std::vector<std::shared_ptr<Product>> Product::readProductsFromInput(std::istream& ss)
{
	std::vector<std::shared_ptr<Product>> products; // Vector to store parsed products.
	std::string line;

	while (std::getline(ss, line)) { // Reads each line of input.
		std::istringstream iss(line); // Parses line as a stream.
		size_t id;
		std::string name, description, categoryStr, manufacturer;
		double price, weight;
		Dimensions dimensions;
		ProductFactory *factory = ProductFactory::getInstance(); // Singleton instance of ProductFactory.

		// Input format: id,name,description,category,price,weight,manufacturer,length,width,height
		std::string idStr, priceStr, weightStr, lengthStr, widthStr, heightStr;

		// Parse the mandatory fields.
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
			// Skip the line if required fields are missing.
			continue;
		}

		try {
			// Convert strings to appropriate types.
			id = std::stoull(idStr);
			price = std::stod(priceStr);
			weight = std::stod(weightStr);
			dimensions.length = std::stod(lengthStr);
			dimensions.width = std::stod(widthStr);
			dimensions.height = std::stod(heightStr);
		} catch (const std::exception &e) {
			// Handle conversion errors and continue to the next line.
			std::cout << "Input error: " << e.what() << " ";
			continue;
		}

		// If the category is not "unknown", parse additional fields.
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
