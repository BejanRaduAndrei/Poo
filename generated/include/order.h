// Order.h
#ifndef ORDER_H
#define ORDER_H

#include "products/product.h"
#include "user.h"
#include <vector>
#include <string>
#include <memory>
#include "payment/payment.h"
#include "payment/cardPayment.h"
#include "payment/onlinePayment.h"
#include "payment/cashPayment.h"

class Order {
private:
    int orderId;
    User user;
    ShoppingCart cart;
    std::string status;
    std::unique_ptr<Payment> paymentMethod;

public:
    Order(int orderId, const User& customer, const ShoppingCart& cart)
        : orderId(orderId), user(customer), cart(cart), status("Pending") {
        this->paymentMethod = nullptr;
    }

    int getOrderId() const { return orderId; }
    User getUser() const { return user; }
    const ShoppingCart& getCart() const { return cart; }
    double getTotalAmount() const { return cart.totalPrice(); }
    const std::string& getStatus() const { return status; }

    void updateStatus(const std::string& newStatus) {
        status = newStatus;
    }

    void handlePayment(std::unique_ptr<Payment> payment) {
        this->paymentMethod = std::move(payment);
        this->paymentMethod->pay(cart.totalPrice());
        status = "Paid";
    }
    void handleRefund() {
        this->paymentMethod->refund();
        status = "Refunded";
    }

    void processSpecificPayment() {
        if (auto cardPayment = dynamic_cast<CardPayment*>(paymentMethod.get())) {
            std::cout << "Processing card payment with card number: " << cardPayment->getCardNumber() << std::endl;
        } else if (auto cashPayment = dynamic_cast<CashPayment*>(paymentMethod.get())) {
            std::cout << "Processing cash payment." << std::endl;
        } else if (auto onlinePayment = dynamic_cast<OnlinePayment*>(paymentMethod.get())) {
            std::cout << "Processing online payment with email: " << user.getEmail() << std::endl;
        } else {
            std::cout << "Unknown payment method." << std::endl;
        }
    }
    
};

#endif // ORDER_H