#ifndef __CASH_PAYMENT_H__
#define __CASH_PAYMENT_H__

#include "payment/payment.h"
#include <iostream>

class CashPayment : public Payment {
    CashPayment() {

    }
    ~CashPayment() {

    }
    void pay(double sum) override {
        std::cout << "Cash payment: " << sum << std::endl;
        std::cout << "Pay at the arrival" << std::endl;
    }
    void refund(double sum) override {
        std::cout << "Cash refund: " << sum << std::endl;
        std::cout << "Go to our offices to get your money back" << std::endl;
    }
};

#endif