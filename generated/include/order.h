// Order.h
#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include "user.h"
#include <vector>
#include <string>
#include <memory>
#include "payment/payment.h"

class Order {
private:
    int orderId;
    User user;
    std::vector<std::pair<Product, int>> products;
    double totalAmount;
    std::string status;
    std::unique_ptr<Payment> payment;
    bool isPaid;

public:
    Order(int orderId, const User& customer, const std::vector<std::pair<Product, int>>& products)
        : orderId(orderId), user(customer), products(products), status("Pending") {
        totalAmount = 0.0;
        for (const auto& item : products) {
            totalAmount += item.first.getPrice() * item.second;
        }
        this->payment = nullptr;
        this->isPaid = false;
    }

    int getOrderId() const { return orderId; }
    User getUser() const { return user; }
    std::vector<std::pair<Product, int>> getProducts() const { return products; }
    double getTotalAmount() const { return totalAmount; }
    std::string getStatus() const { return status; }

    void updateStatus(const std::string& newStatus) {
        status = newStatus;
    }

    void handlePayment(std::unique_ptr<Payment> payment) {
        this->payment = std::move(payment);
        this->payment->pay(totalAmount);
        this->isPaid = true;
    }
    void handleRefund() {
        this->payment->refund(totalAmount);
        this->isPaid = false;
    }
};

#endif // ORDER_H