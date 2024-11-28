#ifndef __CARD_PAYMENT_H__
#define __CARD_PAYMENT_H__

#include "payment/payment.h"
#include <iostream>

class CardPayment : public Payment {
    std::string cardNumber;
public:
    CardPayment(const std::string& cardNumber) {
        this->cardNumber = cardNumber;
    }
    ~CardPayment() {
    }
    void pay(double sum) override {
        std::cout << "Card payment: " << sum << std::endl;
        std::cout << "Taken to the provider that handles these payments" << std::endl;
    }
    void refund(double sum) override {
        std::cout << "Card refund: " << sum << std::endl;
        std::cout << "Taken to the provider that handles these payments" << std::endl;
    }
};

#endif