#ifndef __PAYMENT_H__
#define __PAYMENT_H__

class Payment {
public:
    Payment() {

    }
    virtual ~Payment() {
        
    }
    virtual void pay(double sum) = 0;
    virtual void refund() = 0;
};

#endif