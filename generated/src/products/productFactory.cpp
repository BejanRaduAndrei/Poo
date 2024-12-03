#include <memory>

#include "products/productFactory.h"
#include "products/book.h"
#include "products/clothing.h"
#include "products/electronics.h"
#include "products/furniture.h"
#include "products/sports.h"

// Singleton instance of ProductFactory.
std::unique_ptr<ProductFactory> ProductFactory::instance = nullptr;

// Returns the singleton instance of ProductFactory, creating it if necessary.
ProductFactory *ProductFactory::getInstance()
{
	if (instance == nullptr) { // Lazy initialization of the singleton.
		instance = std::make_unique<ProductFactory>();
	}
	return instance.get();
}

// Factory method: Creates a product object based on the specified category and parameters.
std::shared_ptr<Product> ProductFactory::createProduct(
	const std::string &category, size_t id, const std::string &name,
	const std::string &description, double price, double weight,
	const std::string &manufacturer, const Dimensions &dimensions,
	const std::string &extra1, const std::string &extra2,
	const std::string &extra3)
{
	if (category == "unknown") {
		// Create a generic Product if the category is unknown.
		return std::make_shared<Product>(id, name, description, price,
						 weight, manufacturer,
						 dimensions);
	}
	if (category == "book") {
		// Create a Book product with specific attributes (e.g., author, genre).
		return std::make_shared<Book>(id, name, description, price,
					      weight, manufacturer, dimensions,
					      extra1, extra2, extra3);
	}
	if (category == "electronics") {
		// Create an Electronics product (e.g., brand, model).
		return std::make_shared<Electronics>(id, name, description,
						     price, weight,
						     manufacturer, dimensions,
						     extra1, extra2, extra3);
	}
	if (category == "sports") {
		// Create a Sports product (e.g., sport type, material).
		return std::make_shared<Sports>(id, name, description, price,
						weight, manufacturer,
						dimensions, extra1, extra2,
						extra3);
	}
	if (category == "furniture") {
		// Create a Furniture product (e.g., material, room type).
		return std::make_shared<Furniture>(id, name, description, price,
						   weight, manufacturer,
						   dimensions, extra1, extra2,
						   extra3);
	}
	if (category == "clothing") {
		// Create a Clothing product (e.g., size, fabric type).
		return std::make_shared<Clothing>(id, name, description, price,
						  weight, manufacturer,
						  dimensions, extra1, extra2,
						  extra3);
	}
	// Default: Create a generic Product if no category matches.
	return std::make_shared<Product>(id, name, description, price, weight,
					 manufacturer, dimensions);
}

// Overloaded factory method: Creates a generic Product without category-specific attributes.
std::shared_ptr<Product> ProductFactory::createProduct(
	size_t id, const std::string &name,
	const std::string &description, double price, double weight,
	const std::string &manufacturer, const Dimensions &dimensions)
{
	return std::make_shared<Product>(id, name, description, price, weight,
					 manufacturer, dimensions);
}
