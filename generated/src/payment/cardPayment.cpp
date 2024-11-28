#include "payment/cardPayment.h"

CardPayment::CardPayment(const std::string &cardNumber)
{
	this->cardNumber = cardNumber;
	if (cardNumber.size() != 16) {
		throw InvalidCardException();
	}
}
CardPayment::~CardPayment()
{
}