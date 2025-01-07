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
    unsigned loyaltyPoints{0};     // User's loyalty points
    static constexpr double POINTS_PER_DOLLAR = 10; // Points per dollar spent

public:
    User(); // Default constructor
    User(const std::string& name, const std::string& email, const std::string& password); // Parameterized constructor
    ~User(); // Destructor

    // Getters for user information
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getAddress() const;
    const std::string& getPhoneNumber() const;

    ShoppingCart& getCart() {
        return cart;
    }

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
    void clearWishlist();
    uint64_t getWishlistSize() const {
        return wishlist.getCartSize();
    }
    double getTotalPrice() const;
    size_t getCartSize() const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
    void saveToFile(const std::string& filename) const;    

    // Loyalty points operations
    void addLoyaltyPoints(double purchaseAmount) {
        loyaltyPoints += static_cast<unsigned>(purchaseAmount * POINTS_PER_DOLLAR);
    }

    unsigned getLoyaltyPoints() const { return loyaltyPoints; }

    double getLoyaltyDiscount() const {
        return (loyaltyPoints >= 1000) ? 0.05 :  // 5% discount for 1000+ points
               (loyaltyPoints >= 500) ? 0.03 :   // 3% discount for 500+ points
               0.0;                              // No discount
    }
};

#endif