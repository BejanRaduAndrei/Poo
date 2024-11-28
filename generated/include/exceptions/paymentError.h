#ifndef __PAYMENT_ERROR_H__
#define __PAYMENT_ERROR_H__

#include <stdexcept>
class PaymentError: public std::runtime_error {
public:
    PaymentError(const std::string& message) : std::runtime_error(message) {}
};

#endif