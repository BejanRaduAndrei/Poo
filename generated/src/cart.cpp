#include <cart.h>
#include <iostream>

ShoppingCart::ShoppingCart() {
    this->createdAt = time(NULL);
    this->updatedAt = this->createdAt;
}

ShoppingCart::ShoppingCart(const ShoppingCart& other) {
    this->products = other.products;
    this->createdAt = other.createdAt;
    this->updatedAt = other.updatedAt;
}

ShoppingCart::~ShoppingCart() {
    this->products.clear();
    this->createdAt = 0;
    this->updatedAt = 0;
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other) noexcept {
    if(this == &other) {
        return *this;
    }
    this->products = other.products;
    this->createdAt = other.createdAt;
    this->updatedAt = other.updatedAt;
    return *this;
}

void ShoppingCart::addProduct(const Product& product, size_t quantity) {
    this->products.emplace_front(std::make_pair(product, quantity));
    this->updatedAt = time(NULL);
}

void ShoppingCart::removeProduct(size_t id) {
    this->products.remove_if([id](const std::pair<Product, size_t>&p){return p.first.getID() == id;});
    this->updatedAt = time(NULL);
}

void ShoppingCart::clearCart() {
    this->products.clear();
    this->updatedAt = time(NULL);
}

double ShoppingCart::totalPrice() const{
    double sum = 0.0;
    for(const std::pair<Product, long long>& p: this->products) {
        sum += p.first.getPrice() * p.second;
    }
    return sum;
}

size_t ShoppingCart::getCartSize() const {
    return this->products.size();
}

std::ostream& operator<<(std::ostream& os, const ShoppingCart& obj) {
    for(const std::pair<Product, long long>& p: obj.products) {
        os << "----------------\n";
        os << p.first;
        os << "Quantity: " << p.second << '\n';
    }
    return os;
}