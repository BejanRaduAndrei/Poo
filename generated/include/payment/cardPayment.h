#ifndef __CARD_PAYMENT_H__
#define __CARD_PAYMENT_H__

#include "payment/payment.h"         // Base Payment class header
#include "exceptions/paymentError.h" // Exception classes for payment errors
#include <iostream>                  // For std::cout

// CardPayment class derived from PaymentStrategy
class CardPayment : public PaymentStrategy {
    std::string cardNumber; // Card number for payment
    size_t sum;             // Amount paid

public:
    CardPayment(const std::string& cardNumber); // Constructor
    ~CardPayment();                             // Destructor

    // Override pay method for card payment
    void pay(double sum) override {
        // Simulate insufficient funds exception for large sums
        if (sum > 1000) {
            throw InsufficientFundsException();
        }
        this->sum = sum; // Store the amount paid
        std::cout << "Paid " << sum << " with card " << cardNumber << std::endl;
    }

    // Get the card number
    const std::string& getCardNumber() {
        return cardNumber;
    }

    // Override refund method for card payment
    void refund() override {
        std::cout << "Refunded " << sum << " to card " << cardNumber << std::endl;
    }
};

#endif
