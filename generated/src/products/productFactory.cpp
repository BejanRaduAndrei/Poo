#include <memory>

#include "products/productFactory.h"
#include "products/book.h"
#include "products/clothing.h"
#include "products/electronics.h"
#include "products/furniture.h"
#include "products/sports.h"

std::unique_ptr<ProductFactory> ProductFactory::instance = nullptr;

ProductFactory *ProductFactory::getInstance()
{
	if (instance == nullptr) {
		instance = std::make_unique<ProductFactory>();
	}
	return instance.get();
}
std::shared_ptr<Product> ProductFactory::createProduct(
	const std::string &category, size_t id, const std::string &name,
	const std::string &description, double price, double weight,
	const std::string &manufacturer, const Dimensions &dimensions,
	const std::string &extra1, const std::string &extra2,
	const std::string &extra3)
{
	if (category == "unknown") {
		return std::make_shared<Product>(id, name, description, price,
						 weight, manufacturer,
						 dimensions);
	}
	if (category == "book") {
		return std::make_shared<Book>(id, name, description, price,
					      weight, manufacturer, dimensions,
					      extra1, extra2, extra3);
	}
	if (category == "electronics") {
		return std::make_shared<Electronics>(id, name, description,
						     price, weight,
						     manufacturer, dimensions,
						     extra1, extra2, extra3);
	}
	if (category == "sports") {
		return std::make_shared<Sports>(id, name, description, price,
						weight, manufacturer,
						dimensions, extra1, extra2,
						extra3);
	}
	if (category == "furniture") {
		return std::make_shared<Furniture>(id, name, description, price,
						   weight, manufacturer,
						   dimensions, extra1, extra2,
						   extra3);
	}
	if (category == "clothing") {
		return std::make_shared<Clothing>(id, name, description, price,
						  weight, manufacturer,
						  dimensions, extra1, extra2,
						  extra3);
	}
	return std::make_shared<Product>(id, name, description, price, weight,
					 manufacturer, dimensions);
}

std::shared_ptr<Product> ProductFactory::createProduct(
	size_t id, const std::string &name,
	const std::string &description, double price, double weight,
	const std::string &manufacturer, const Dimensions &dimensions)
{
	return std::make_shared<Product>(id, name, description, price, weight,
					 manufacturer, dimensions);
}