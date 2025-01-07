#ifndef __SHOPPING_CART_H__
#define __SHOPPING_CART_H__

#include "cart/baseCart.h"
#include <stdexcept>
#include <chrono>

class ShoppingCart : public BaseCart {
    static const size_t MAX_QUANTITY_PER_ITEM = 10;
    static constexpr std::chrono::seconds EXPIRATION_TIME{1}; // Items expire after 30 minutes
    std::chrono::system_clock::time_point lastUpdateTime;

public:
    ShoppingCart() = default;
    ShoppingCart(const ShoppingCart& other) = default;
    ~ShoppingCart() = default;
    ShoppingCart& operator=(const ShoppingCart& other) noexcept = default;

    // Override addProduct to enforce quantity limit
    void addProduct(const std::shared_ptr<Product>& product, size_t quantity) {
        if (quantity > MAX_QUANTITY_PER_ITEM) {
            throw std::runtime_error("Cannot add more than " + 
                std::to_string(MAX_QUANTITY_PER_ITEM) + " units of the same product");
        }
        lastUpdateTime = std::chrono::system_clock::now();
        BaseCart::addProduct(product, quantity);
    }

    static size_t getMaxQuantityPerItem() { return MAX_QUANTITY_PER_ITEM; }

    bool isExpired() const {
        auto now = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdateTime) > EXPIRATION_TIME;
    }

    void refreshExpiration() {
        lastUpdateTime = std::chrono::system_clock::now();
    }
};

#endif
