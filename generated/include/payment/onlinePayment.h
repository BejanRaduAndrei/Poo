#ifndef __ONLINE_PAYMENT_H__
#define __ONLINE_PAYMENT_H__

#include "payment/payment.h"
#include "exceptions/paymentError.h"
#include <iostream>

class OnlinePayment : public Payment {
    std::string cardNumber;
    size_t sum;

public:
    OnlinePayment(const std::string &cardNumber) : cardNumber(cardNumber) {}
    void pay(double sum) override {
        // Simulate a timeout
        if (sum == 100) {
            throw PaymentTimeoutException();
        }
        this->sum = sum;
        std::cout << "Paid " << sum << " with card " << cardNumber << std::endl;
    }
    void refund() override {
        std::cout << "Refunded " << sum << " to card " << cardNumber << std::endl;
    }
};

#endif