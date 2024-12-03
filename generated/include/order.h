// Order.h
#ifndef ORDER_H
#define ORDER_H

#include "products/product.h"     // Product class header
#include "user.h"                 // User class header
#include <vector>
#include <string>
#include <memory>
#include "payment/payment.h"      // Base Payment class header
#include "payment/cardPayment.h"  // CardPayment class header
#include "payment/onlinePayment.h"// OnlinePayment class header
#include "payment/cashPayment.h"  // CashPayment class header

// Order class definition
class Order {
private:
    int orderId;                            // Unique order ID
    User user;                              // User who placed the order
    ShoppingCart cart;                      // Shopping cart for the order
    std::string status;                     // Current order status
    std::unique_ptr<Payment> paymentMethod; // Payment method used for the order

public:
    // Constructor
    Order(int orderId, const User& customer, const ShoppingCart& cart)
        : orderId(orderId), user(customer), cart(cart), status("Pending") {
        this->paymentMethod = nullptr;
    }

    // Getters
    int getOrderId() const { return orderId; }
    User getUser() const { return user; }
    const ShoppingCart& getCart() const { return cart; }
    double getTotalAmount() const { return cart.totalPrice(); }
    const std::string& getStatus() const { return status; }

    // Update order status
    void updateStatus(const std::string& newStatus) {
        status = newStatus;
    }

    // Handle payment using a specific payment method
    void handlePayment(std::unique_ptr<Payment> payment) {
        this->paymentMethod = std::move(payment); // Set payment method
        this->paymentMethod->pay(cart.totalPrice()); // Process payment
        status = "Paid"; // Update status
    }

    // Handle refund for the order
    void handleRefund() {
        this->paymentMethod->refund(); // Process refund
        status = "Refunded";           // Update status
    }

    // Process specific payment type with additional details
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