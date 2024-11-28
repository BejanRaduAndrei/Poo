#include "cart/shoppingCart.h"
#include "cart/baseCart.h"

void ShoppingCart::applyDiscount(double percentage)
{
	this->discount = std::make_optional<double>(percentage);
}