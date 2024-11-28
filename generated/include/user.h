#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <cart/shoppingCart.h>
#include <cart/wishlistCart.h>

class User {
    size_t id;
    std::string name;
    std::string email;
    // Hashed password
    std::string password;
    std::string address;
    std::string phoneNumber;
    ShoppingCart cart;
    WishlistCart wishlist;
public:
    User();
    User(const std::string& name, const std::string& email, const std::string& password);
    ~User();

    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getAddress() const;
    const std::string& getPhoneNumber() const;

    void updateProfile(const std::string& name, const std::string& email, const std::string& address, const std::string& phoneNumber);
    // newPassword is supposed to be hashed
    void changePassword(const std::string& newPassword);
    void addToCart(const Product& product, long long quantity);
    void removeFromCart(const long long productId);
    void addToWishlist(const Product& product, long long quantity);
    void removeFromWishlist(const long long productId);
    void clearCart();
    void clearWishlist();
    double getTotalPrice() const;
    size_t getCartSize() const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
    void saveToFile(const std::string& filename) const;    
};

#endif