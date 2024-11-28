#ifndef __WISH_LIST_CART_H__
#define __WISH_LIST_CART_H__

#include "cart/baseCart.h"
#include "exceptions/wishlistError.h"

class WishlistCart : public BaseCart {
public:
    WishlistCart() = default;
    WishlistCart(const WishlistCart& other) = default;
    ~WishlistCart() = default;
    WishlistCart& operator=(const WishlistCart& other) noexcept = default;
    virtual double totalPrice() {
        throw WishlistError("Wishlist cart does not have a total price");
    }
};

#endif