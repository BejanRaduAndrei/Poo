#include <user.h>
#include <iostream>
#include <fstream>
#include <id.h>

// Default constructor: Initializes user with default values and a unique ID.
User::User()
	: id(IDGenerator::getInstance()->getNextID())
	, name("")
	, email("")
	, password("")
	, address("")
	, phoneNumber("")
{
}

// Parameterized constructor: Sets name, email, and password, and assigns a unique ID.
User::User(const std::string &name, const std::string &email,
	   const std::string &password)
	: id(IDGenerator::getInstance()->getNextID())
	, name(name)
	, email(email)
	, password(password)
{
}

// Destructor: Explicitly defined (currently no custom cleanup needed).
User::~User()
{
}

// Updates user's profile with new details.
void User::updateProfile(const std::string &userName, const std::string &userEmail,
			 const std::string &userAddress,
			 const std::string &userPhoneNumber)
{
	this->name = userName;
	this->email = userEmail;
	this->address = userAddress;
	this->phoneNumber = userPhoneNumber;
}

// Changes the user's password.
void User::changePassword(const std::string &newPassword)
{
	this->password = newPassword;
}

// Adds a product to the cart with specified quantity.
void User::addToCart(const std::shared_ptr<Product> &product, long long quantity)
{
	cart.addProduct(product, quantity);
}

// Removes a product from the cart by product ID.
void User::removeFromCart(const long long productId)
{
	cart.removeProduct(productId);
}

// Adds a product to the wishlist with specified quantity.
void User::addToWishlist(const std::shared_ptr<Product> &product, long long quantity)
{
	wishlist.addProduct(product, quantity);
}

// Removes a product from the wishlist by product ID.
void User::removeFromWishlist(const long long productId)
{
	wishlist.removeProduct(productId);
}

// Clears all items from the cart.
void User::clearCart()
{
	cart.clearCart();
}

// Returns the total price of items in the cart.
double User::getTotalPrice() const
{
	return cart.totalPrice();
}

// Returns the number of items in the cart.
size_t User::getCartSize() const
{
	return cart.getCartSize();
}

// Overloaded output operator: Outputs user details and cart information.
std::ostream &operator<<(std::ostream &os, const User &user)
{
	os << "User Id: " << user.id << '\n';
	os << "Name: " << user.name << '\n';
	os << "Email: " << user.email << '\n';
	os << "Address: " << user.address << '\n';
	os << "Phone Number: " << user.phoneNumber << '\n';
	os << "Cart: " << user.cart << '\n';
	return os;
}

// Returns the user's name.
const std::string &User::getName() const
{
	return this->name;
}

// Returns the user's email.
const std::string &User::getEmail() const
{
	return this->email;
}

// Returns the user's address.
const std::string &User::getAddress() const
{
	return this->address;
}

// Returns the user's phone number.
const std::string &User::getPhoneNumber() const
{
	return this->phoneNumber;
}

// Saves the user's profile and cart details to a file.
// Warning: Password is saved in plaintext.
void User::saveToFile(const std::string &filename) const
{
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << "\n";
		return;
	}

	file << id << "\n";
	file << name << "\n";
	file << email << "\n";
	file << password << "\n";
	file << address << "\n";
	file << phoneNumber << "\n";
	file << cart.totalPrice() << "\n";

	file.close();
}