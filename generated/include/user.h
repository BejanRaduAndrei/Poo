#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <cart/shoppingCart.h>
#include <cart/wishlistCart.h>
#include <memory>

// User class definition
class User {
    size_t id;                     // User ID
    std::string name;              // User name
    std::string email;             // User email
    std::string password;          // Hashed password
    std::string address;           // User address
    std::string phoneNumber;       // User phone number
    ShoppingCart cart;             // User's shopping cart
    WishlistCart wishlist;         // User's wishlist

public:
    User(); // Default constructor
    User(const std::string& name, const std::string& email, const std::string& password); // Parameterized constructor
    ~User(); // Destructor

    // Getters for user information
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getAddress() const;
    const std::string& getPhoneNumber() const;

    // Update user profile details
    void updateProfile(const std::string& name, const std::string& email, const std::string& address, const std::string& phoneNumber);

    // Change user's password (newPassword should be hashed)
    void changePassword(const std::string& newPassword);

    // Cart-related operations
    void addToCart(const std::shared_ptr<Product>& product, long long quantity);
    void removeFromCart(const long long productId);
    void clearCart();

    // Wishlist-related operations
    void addToWishlist(const std::shared_ptr<Product>& product, long long quantity);
    void removeFromWishlist(const long long productId);
    void clearCart();
    void clearWishlist();
    double getTotalPrice() const;
    size_t getCartSize() const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
    void saveToFile(const std::string& filename) const;    
};

#endif