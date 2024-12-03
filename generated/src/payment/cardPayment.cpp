#include "payment/cardPayment.h"

// Constructor: Initializes a CardPayment object with a card number.
CardPayment::CardPayment(const std::string &cardNumber)
{
	this->cardNumber = cardNumber;

	// Validate the card number length (must be 16 digits).
	if (cardNumber.size() != 16) {
		throw InvalidCardException(); // Throws an exception for invalid card number.
	}
}

// Destructor: Cleans up resources (if any) when the CardPayment object is destroyed.
CardPayment::~CardPayment()
{
	// No specific cleanup is required here.
}