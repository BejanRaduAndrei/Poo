#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <map>
#include <products/product.h>
#include <stdexcept>
#include <iostream>

class Inventory {
    std::map<size_t, size_t> stock;  // productId -> quantity
    std::map<size_t, size_t> reorderLevel;  // productId -> minimum quantity

public:
    void addStock(size_t productId, size_t quantity) {
        stock[productId] += quantity;
    }

    void removeStock(size_t productId, size_t quantity) {
        if (stock[productId] < quantity) 
            throw std::runtime_error("Insufficient stock");
        stock[productId] -= quantity;
        checkReorderLevel(productId);
    }

    void setReorderLevel(size_t productId, size_t level) {
        reorderLevel[productId] = level;
    }

    bool needsReorder(size_t productId) const {
        auto it = stock.find(productId);
        if (it == stock.end()) return false;
        auto rlevel = reorderLevel.find(productId);
        return rlevel != reorderLevel.end() && it->second <= rlevel->second;
    }

private:
    void checkReorderLevel(size_t productId) {
        if (needsReorder(productId)) {
            // Could trigger reorder notification
            std::cout << "Product " << productId << " needs reordering!\n";
        }
    }
};

#endif
