#ifndef __CART_H__
#define __CART_H__

#include <list>

#include <products/product.h>
#include <ctime>

class BaseCart {
    std::list<std::pair<std::shared_ptr<Product>, size_t>> products;
    std::time_t createdAt;
    std::time_t updatedAt;
public:
    BaseCart();
    BaseCart(const BaseCart&);
    ~BaseCart();
    BaseCart& operator=(const BaseCart& other) noexcept;
    void addProduct(const std::shared_ptr<Product>&, size_t);
    void removeProduct(const size_t id);
    void clearCart();
    size_t getCartSize() const;
    friend std::ostream& operator<<(std::ostream& os, const BaseCart& obj);
    virtual double totalPrice() const;
};

#endif