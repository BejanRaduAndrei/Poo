#ifndef __PAYMENT_ERROR_H__
#define __PAYMENT_ERROR_H__

#include <stdexcept>
#include <string>

class PaymentException : public std::exception {
private:
    std::string message;
public:
    explicit PaymentException(const std::string& message) : message(message) {}
    explicit PaymentException(const char* message): message(std::string(message)) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public PaymentException {
public:
    InsufficientFundsException() : PaymentException("Insufficient funds for payment") {}
};

class InvalidCardException : public PaymentException {
public:
    InvalidCardException() : PaymentException("Invalid card number") {}
};

class PaymentTimeoutException : public PaymentException {
public:
    PaymentTimeoutException() : PaymentException("PaymentStrategy process timed out") {}
};


#endif