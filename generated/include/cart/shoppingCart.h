#ifndef __SHOPPING_CART_H__
#define __SHOPPING_CART_H__

#include "cart/baseCart.h"
#include <optional>

class ShoppingCart : public BaseCart {
private:
    std::optional<double> discount;
public:
    ShoppingCart() = default;
    ShoppingCart(const ShoppingCart& other) = default;
    ~ShoppingCart() = default;
    ShoppingCart& operator=(const ShoppingCart& other) noexcept = default;
    void applyDiscount(double percentage);
    double totalPrice() const {
        double basePrice = BaseCart::totalPrice();
        if (this->discount.has_value()) {
            return basePrice * (1 - this->discount.value());
        }
        return basePrice;
    }
};

#endif