#ifndef __CARD_PAYMENT_H__
#define __CARD_PAYMENT_H__

#include "payment/payment.h"
#include "exceptions/paymentError.h"
#include <iostream>

class CardPayment : public Payment {
    std::string cardNumber;
    size_t sum;
public:
    CardPayment(const std::string& cardNumber);
    ~CardPayment();
    void pay(double sum) override {
        // Simulate an exception
        if (sum > 1000) {
            throw InsufficientFundsException();
        }
        this->sum = sum;
        std::cout << "Paid " << sum << " with card " << cardNumber << std::endl;
    }
    const std::string& getCardNumber() {
        return cardNumber;
    }
    void refund() override {
        std::cout << "Refunded " << sum << " to card " << cardNumber << std::endl;
    }
};

#endif