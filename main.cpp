#include <user.h>
#include <cart/shoppingCart.h>
#include <product.h>
#include <iostream>
#include <id.h>
#include <random>
#include <assert.h>
#include <order.h>
#include "payment/cardPayment.h"
#include "payment/cashPayment.h"
#include "payment/onlinePayment.h"

const std::string CARD_NUMBER = "ABCDEF1234567890"; 

void testAdding(User &user) {
    size_t prevLength = user.getCartSize();
    user.addToCart(Product(100, "Coffee", 10), 5);
    assert(user.getCartSize() == prevLength + 1);
}

void testRemoving(User &user) {
    size_t prevLength = user.getCartSize();
    user.removeFromCart(100);
    assert(user.getCartSize() == prevLength - 1);
}

void testClearing(User &user) {
    user.clearCart();
    assert(user.getCartSize() == 0);
}

void testTotalPrice(User &user) {
    double price = user.getTotalPrice();
    assert(price >= 0);
}

void testUser() {
    User user = User("John Doe", "", "");
    assert(user.getName() == "John Doe");
    assert(user.getEmail() == "");
    assert(user.getAddress() == "");
    assert(user.getPhoneNumber() == "");
    user.updateProfile("John Doe", "john.doe@gmail.com", "New York", "014124212421");
    assert(user.getName() == "John Doe");
    assert(user.getEmail() == "john.doe@gmail.com");
    assert(user.getAddress() == "New York");
    assert(user.getPhoneNumber() == "014124212421");
}

void testCopyConstructorShopping() {
    ShoppingCart cart;
    cart.addProduct(Product(100, "Coffee", 10), 5);
    ShoppingCart cart2(cart);
    assert(cart2.getCartSize() == 1);
}

void testCopyAssignmentShopping() {
    ShoppingCart cart;
    cart.addProduct(Product(100, "Coffee", 10), 5);
    ShoppingCart cart2;
    cart2 = cart;
    assert(cart2.getCartSize() == 1);
}

void testDiscount() {
    ShoppingCart cart;
    cart.addProduct(Product(100, "Coffee", 10), 5);
    assert(cart.totalPrice() == 50);
    cart.applyDiscount(0.1);
    assert(cart.totalPrice() == 45);
}


void testOrder(User &user, std::vector<Product> &p) {
    ShoppingCart cart;
    for(int i = 0; i < 5; ++i) {
        cart.addProduct(p.at(i), rand() % 5);
    }
    Order order = Order(1, user, cart);
    assert(order.getOrderId() == 1);
    order.handlePayment(std::make_unique<CardPayment>(CARD_NUMBER));
    assert(order.getStatus() == "Paid");
    order.handleRefund();
    assert(order.getStatus() == "Refunded");
}

void testPayment() {
    try {
        CardPayment cardPayment(CARD_NUMBER);
        cardPayment.pay(100);
        cardPayment.refund();
        CashPayment cashPayment;
        cashPayment.pay(50);
        cashPayment.refund();
        OnlinePayment onlinePayment("john.doe@gmail.com");
        onlinePayment.pay(200);
        onlinePayment.refund();
        cardPayment.pay(1200);
    } catch (const std::exception& e) {
        if (const auto* invalidCard = dynamic_cast<const InvalidCardException*>(&e)) {
            std::cout << "Invalid card exception: " << invalidCard->what() << '\n';
        } else if (const auto* insufficientFunds = dynamic_cast<const InsufficientFundsException*>(&e)) {
            std::cout << "Insufficient funds exception: " << insufficientFunds->what() << '\n';
        } else if (const auto* paymentTimeout = dynamic_cast<const PaymentTimeoutException*>(&e)) {
            std::cout << "Payment timeout exception: " << paymentTimeout->what() << '\n';
        } else {
            std::cout << "Unknown payment exception: " << e.what() << '\n';
        }
    }
}

void testDynamicCast(User& user, std::vector<Product>& p) {
    ShoppingCart cart;
    for(int i = 0; i < 2; ++i) {
        cart.addProduct(p.at(i), rand() % 2);
    }
    Order order = Order(1, user, cart);
    assert(order.getOrderId() == 1);
    try {
        order.handlePayment(std::make_unique<CardPayment>(CARD_NUMBER));
        order.processSpecificPayment();    
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }
}


int main() {
    testUser();
    testCopyConstructorShopping();
    testCopyAssignmentShopping();
    srand(0);
    std::vector<Product> products = Product::readProductsFromStdin();
    User user = User("John Doe", "john.doe@gmail.com", "password");
    user.updateProfile("John Doe", "john.doe@gmail.com", "New York", "014124212421");
    for(int i = 0; i < 5; ++i) {
        user.addToCart(products.at(i), rand() % 5);
    }
    std::cout << user << '\n';
    testAdding(user);
    testRemoving(user);
    testTotalPrice(user);
    testClearing(user);
    testDiscount();
    testPayment();
    testOrder(user, products);
    testDynamicCast(user, products);
}