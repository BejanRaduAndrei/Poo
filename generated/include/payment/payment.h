#ifndef __PAYMENT_H__
#define __PAYMENT_H__

#include "exceptions/abstractClassError.h"

class Payment {
public:
    Payment() {
        throw AbstractClassError();
    }
    ~Payment() {
        throw AbstractClassError();
    }
    virtual void pay(double sum);
    virtual void refund(double sum);
};

#endif