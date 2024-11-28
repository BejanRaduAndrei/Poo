#include "cart/shoppingCart.h"
#include "cart/baseCart.h"

ShoppingCart::ShoppingCart()
{
	this->discount = std::nullopt;
	BaseCart();
};

void ShoppingCart::applyDiscount(double percentage)
{
	this->discount = std::make_optional<double>(percentage);
}