#include <user.h>
#include <cart.h>
#include <product.h>
#include <iostream>
#include <random>
#include <assert.h>

void testAdding(User &user) {
    size_t prevLength = user.getCartSize();
    user.addToCart(Product(100, "Coffee"), 5);
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
    cart.addProduct(Product(100, "Coffee"), 5);
    ShoppingCart cart2(cart);
    assert(cart2.getCartSize() == 1);
}

void testCopyAssignmentShopping() {
    ShoppingCart cart;
    cart.addProduct(Product(100, "Coffee"), 5);
    ShoppingCart cart2;
    cart2 = cart;
    assert(cart2.getCartSize() == 1);
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
}