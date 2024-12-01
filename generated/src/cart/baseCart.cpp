#include <cart/baseCart.h>
#include <iostream>

BaseCart::BaseCart()
{
	this->createdAt = time(NULL);
	this->updatedAt = this->createdAt;
}

BaseCart::BaseCart(const BaseCart &other)
{
	this->products = other.products;
	this->createdAt = other.createdAt;
	this->updatedAt = other.updatedAt;
}

BaseCart::~BaseCart()
{
	this->products.clear();
	this->createdAt = 0;
	this->updatedAt = 0;
}

BaseCart &BaseCart::operator=(const BaseCart &other) noexcept
{
	if (this == &other) {
		return *this;
	}
	this->products = other.products;
	this->createdAt = other.createdAt;
	this->updatedAt = other.updatedAt;
	return *this;
}

void BaseCart::addProduct(const std::shared_ptr<Product> &product,
			  size_t quantity)
{
	this->products.emplace_front(std::make_pair(product, quantity));
	this->updatedAt = time(NULL);
}

void BaseCart::removeProduct(size_t id)
{
	this->products.remove_if(
		[id](const std::pair<std::shared_ptr<Product>, size_t> p) {
			return p.first.get()->getID() == id;
		});
	this->updatedAt = time(NULL);
}

void BaseCart::clearCart()
{
	this->products.clear();
	this->updatedAt = time(NULL);
}

double BaseCart::totalPrice() const
{
	double sum = 0.0;
	for (const auto &p : this->products) {
		sum += p.first.get()->getPrice() * p.second;
	}
	return sum;
}

size_t BaseCart::getCartSize() const
{
	return this->products.size();
}

std::ostream &operator<<(std::ostream &os, const BaseCart &obj)
{
	for (const auto &p : obj.products) {
		os << "----------------\n";
		os << *p.first;
		os << "Quantity: " << p.second << '\n';
	}
	return os;
}