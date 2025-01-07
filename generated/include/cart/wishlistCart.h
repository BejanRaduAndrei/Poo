#ifndef __WISH_LIST_CART_H__
#define __WISH_LIST_CART_H__

#include "cart/baseCart.h"
#include <map>

class WishlistCart : public BaseCart {
    std::map<size_t, double> priceHistory; // Track price changes by product ID
    double priceDropThreshold{0.1}; // 10% price drop notification threshold

public:
    WishlistCart() = default;
    WishlistCart(const WishlistCart& other) = default;
    ~WishlistCart() = default;
    WishlistCart& operator=(const WishlistCart& other) noexcept = default;

    void addProduct(const std::shared_ptr<Product>& product, size_t quantity) {
        auto id = product->getID();
        double newPrice = product->getPrice();
        
        // Only store initial price if not already tracked
        if (priceHistory.find(id) == priceHistory.end()) {
            priceHistory[id] = newPrice;
        }
        BaseCart::addProduct(product, quantity);
    }

    bool checkPriceDrops(std::vector<std::pair<size_t, double>>& drops) const {
        drops.clear();  // Clear any existing entries
        bool foundDrops = false;
        
        for (const auto& item : priceHistory) {
            auto product = getProductById(item.first);
            if (!product) continue;  // Skip if product not found
            
            double initialPrice = item.second;
            double currentPrice = product->getPrice();
            
            if (currentPrice < initialPrice * (1.0 - priceDropThreshold)) {
                drops.emplace_back(item.first, currentPrice);
                foundDrops = true;
            }
        }
        return foundDrops;
    }

    void setPriceDropThreshold(double threshold) {
        if (threshold > 0 && threshold < 1) {
            priceDropThreshold = threshold;
        }
    }
    double getProductPrice(size_t id) const {
        return getProductById(id)->getPrice();
    }

};

#endif