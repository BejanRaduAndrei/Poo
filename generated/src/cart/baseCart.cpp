#include <cart/baseCart.h> // BaseCart class header
#include <iostream>        // For std::ostream

// Default constructor
BaseCart::BaseCart()
{
	this->createdAt = time(NULL);    // Set creation time
	this->updatedAt = this->createdAt; // Initialize updated time
}

// Copy constructor
BaseCart::BaseCart(const BaseCart &other)
{
	this->products = other.products; // Copy product list
	this->createdAt = other.createdAt; // Copy creation time
	this->updatedAt = other.updatedAt; // Copy updated time
}

// Destructor
BaseCart::~BaseCart()
{
	this->products.clear(); // Clear product list
	this->createdAt = 0;    // Reset timestamps
	this->updatedAt = 0;
}

// Copy assignment operator
BaseCart &BaseCart::operator=(const BaseCart &other) noexcept
{
	if (this == &other) { // Handle self-assignment
		return *this;
	}
	this->products = other.products; // Copy product list
	this->createdAt = other.createdAt; // Copy creation time
	this->updatedAt = other.updatedAt; // Copy updated time
	return *this;
}

// Add a product to the cart
void BaseCart::addProduct(const std::shared_ptr<Product> &product,
			  size_t quantity)
{
	this->products.emplace_front(std::make_pair(product, quantity)); // Add product
	this->updatedAt = time(NULL);                                    // Update timestamp
}

// Remove a product by ID
void BaseCart::removeProduct(size_t id)
{
	this->products.remove_if(
		[id](const std::pair<std::shared_ptr<Product>, size_t> p) {
			return p.first.get()->getID() == id; // Match product ID
		});
	this->updatedAt = time(NULL); // Update timestamp
}

// Clear the cart
void BaseCart::clearCart()
{
	this->products.clear();  // Clear all products
	this->updatedAt = time(NULL); // Update timestamp
}

// Calculate total price of items in the cart
double BaseCart::totalPrice() const
{
	double sum = 0.0;
	for (const auto &p : this->products) {
		sum += p.first.get()->getPrice() * p.second; // Accumulate product prices
	}
	return sum;
}

// Get the number of items in the cart
size_t BaseCart::getCartSize() const
{
	return this->products.size();
}

// Overload << operator for printing cart contents
std::ostream &operator<<(std::ostream &os, const BaseCart &obj)
{
	for (const auto &p : obj.products) {
		os << "----------------\n";
		os << *p.first;               // Print product details
		os << "Quantity: " << p.second << '\n'; // Print quantity
	}
	return os;
}