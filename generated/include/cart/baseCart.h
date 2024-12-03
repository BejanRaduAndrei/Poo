#ifndef __CART_H__
#define __CART_H__

#include <list>
#include <products/product.h> // Product class header
#include <ctime>              // For time_t

// BaseCart class definition
class BaseCart {
    std::list<std::pair<std::shared_ptr<Product>, size_t>> products; // List of products and their quantities
    std::time_t createdAt;   // Time of cart creation
    std::time_t updatedAt;   // Last updated time

public:
    BaseCart();                            // Default constructor
    BaseCart(const BaseCart&);             // Copy constructor
    ~BaseCart();                           // Destructor
    BaseCart& operator=(const BaseCart& other) noexcept; // Assignment operator

    // Add a product to the cart
    void addProduct(const std::shared_ptr<Product>&, size_t);
    // Remove a product from the cart by ID
    void removeProduct(const size_t id);
    // Clear all products from the cart
    void clearCart();
    // Get the number of products in the cart
    size_t getCartSize() const;
    // Print the cart contents
    friend std::ostream& operator<<(std::ostream& os, const BaseCart& obj);
    // Calculate the total price of the cart
    virtual double totalPrice() const;
};

#endif
