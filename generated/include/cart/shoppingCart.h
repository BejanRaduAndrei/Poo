#ifndef __SHOPPING_CART_H__
#define __SHOPPING_CART_H__

#include "cart/baseCart.h" // BaseCart class header
#include <optional>        // For std::optional

// ShoppingCart class derived from BaseCart
class ShoppingCart : public BaseCart {
private:
    std::optional<double> discount; // Optional discount percentage

public:
    ShoppingCart();                                    // Default constructor
    ShoppingCart(const ShoppingCart& other) = default; // Copy constructor (default)
    ~ShoppingCart() = default;                        // Destructor (default)
    ShoppingCart& operator=(const ShoppingCart& other) noexcept = default; // Assignment operator (default)

    // Apply a discount to the cart
    void applyDiscount(double percentage);

    // Override totalPrice to include discount calculation
    double totalPrice() const {
        double basePrice = BaseCart::totalPrice(); // Get total from base cart
        if (this->discount.has_value()) {
            return basePrice * (1 - this->discount.value()); // Apply discount
        }
        return basePrice; // Return base price if no discount
    }
};

#endif
