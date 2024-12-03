#include "cart/shoppingCart.h" // ShoppingCart class header
#include "cart/baseCart.h"     // BaseCart class header

// Constructor
ShoppingCart::ShoppingCart()
{
    this->discount = std::nullopt; // Initialize discount as no value
    BaseCart();                    // Call BaseCart constructor
};

// Apply a discount to the cart
void ShoppingCart::applyDiscount(double percentage)
{
    this->discount = std::make_optional<double>(percentage); // Set discount
}
