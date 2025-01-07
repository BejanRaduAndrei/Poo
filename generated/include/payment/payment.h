#ifndef __PAYMENT_H__
#define __PAYMENT_H__

class PaymentStrategy {
public:
    PaymentStrategy() {

    }
    virtual ~PaymentStrategy() {
        
    }
    virtual void pay(double sum) = 0;
    virtual void refund() = 0;
};

#endif