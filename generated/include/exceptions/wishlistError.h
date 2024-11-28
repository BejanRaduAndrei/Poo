#ifndef __WISHLIST_ERROR_H__
#define __WISHLIST_ERROR_H__

#include <stdexcept>

class WishlistError : public std::runtime_error {
public:
    WishlistError(const std::string& message) : std::runtime_error(message) {}
};

#endif