#ifndef __CART_H__
#define __CART_H__

#include <list>

#include <product.h>
#include <ctime>

class ShoppingCart {
    std::list<std::pair<Product, long long>> products;
    std::time_t createdAt;
    std::time_t updatedAt;
public:
    ShoppingCart();
    ShoppingCart(const ShoppingCart&);
    ~ShoppingCart();
    ShoppingCart& operator=(const ShoppingCart& other) noexcept;
    void addProduct(const Product&, size_t);
    void removeProduct(const size_t id);
    double totalPrice() const;
    void clearCart();
    size_t getCartSize() const;
    friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& obj);
};

#endif