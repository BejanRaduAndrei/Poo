#include <iostream>
#include <memory>
#include <user.h>
#include <products/product.h>
#include <products/book.h>
#include <products/electronic.h>
#include <products/clothing.h>
#include <cart/shoppingCart.h>
#include <cart/wishlistCart.h>
#include <pricing/priceCalculator.h>
#include <payment/cardPayment.h>
#include <order.h>

int main() {
    // ...existing code for creating products...

    // Create a user and add products to cart
    User user("John Doe", "john@example.com", "password123");
    user.addToCart(std::make_shared<Book>(/* your book parameters */), 2);
    user.addToCart(std::make_shared<Electronic>(/* your electronic parameters */), 1);

    // Use PriceCalculator for shopping cart
    ShoppingCart& userCart = user.getCart();
    PriceCalculator<ShoppingCart> cartCalculator(userCart, 0.19, 0.1); // 19% tax, 10% discount

    std::cout << "Shopping Cart Summary:" << std::endl;
    std::cout << "Subtotal: $" << cartCalculator.calculateSubtotal() << std::endl;
    std::cout << "Tax: $" << cartCalculator.calculateTax() << std::endl;
    std::cout << "Discount: $" << cartCalculator.calculateDiscount() << std::endl;
    std::cout << "Total: $" << cartCalculator.calculateTotal() << std::endl;

    // Create an order with the calculated total
    Order order(1, user, userCart);
    order.handlePayment(std::make_unique<CardPayment>("1234-5678-9012-3456"));
    order.processSpecificPayment();

    // Handle wishlist (note: wishlist typically doesn't need price calculation)
    user.addToWishlist(std::make_shared<Clothing>(/* your clothing parameters */), 1);
    std::cout << "\nWishlist items: " << user.getWishlistSize() << std::endl;

    return 0;
}
