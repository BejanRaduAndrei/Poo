#ifndef __PRICE_CALCULATOR_H__
#define __PRICE_CALCULATOR_H__

#include <type_traits>
#include <cart/baseCart.h>
#include <map>

template<typename CartType>
class PriceCalculator {
    static_assert(std::is_base_of<BaseCart, CartType>::value, 
                  "CartType must be derived from BaseCart");

    CartType& cart;
    double taxRate;
    double discountRate;
    std::map<size_t, double> productDiscounts; // Product-specific discounts

public:
    PriceCalculator(CartType& cart, double taxRate = 0.19, double discountRate = 0.0)
        : cart(cart), taxRate(taxRate), discountRate(discountRate) {}

    double calculateSubtotal() const {
        return cart.totalPrice();
    }

    double calculateTax() const {
        return calculateSubtotal() * taxRate;
    }

    double calculateDiscount() const {
        return calculateSubtotal() * discountRate;
    }

    // Calculate pre-tax total (with discounts but before tax)
    double calculatePreTaxTotal() const {
        return calculateSubtotal() - calculateDiscount() - calculateBulkDiscount();
    }

    // Original calculateTotal now uses pre-tax total
    double calculateTotal() const {
        return calculatePreTaxTotal() + calculateTax();
    }

    void setTaxRate(double newRate) {
        taxRate = newRate;
    }

    void setDiscountRate(double newRate) {
        discountRate = newRate;
    }

    // Add product-specific discount
    void addProductDiscount(size_t productId, double discountPercent) {
        if (discountPercent >= 0 && discountPercent <= 1) {
            productDiscounts[productId] = discountPercent;
        }
    }

    // Calculate price for specific product including its discounts
    double calculateProductPrice(size_t productId) const {
        auto product = cart.getProductById(productId);
        if (!product) return 0.0;

        double basePrice = product->getPrice();
        auto it = productDiscounts.find(productId);
        if (it != productDiscounts.end()) {
            basePrice *= (1.0 - it->second);
        }
        return basePrice;
    }

    // Calculate bulk discount (more items = bigger discount)
    double calculateBulkDiscount() const {
        size_t totalItems = cart.getCartSize();
        double bulkDiscount = 0.0;
        if (totalItems >= 2) bulkDiscount = 0.05;  // Changed from 5 to 2
        if (totalItems >= 5) bulkDiscount = 0.10;  // Changed from 10 to 5
        return calculateSubtotal() * bulkDiscount;
    }

    // Get all discounted products
    std::vector<std::pair<size_t, double>> getDiscountedProducts() const {
        std::vector<std::pair<size_t, double>> discounted;
        for (const auto& [productId, discount] : productDiscounts) {
            if (cart.getProductById(productId)) {
                discounted.emplace_back(productId, discount);
            }
        }
        return discounted;
    }
};

#endif
