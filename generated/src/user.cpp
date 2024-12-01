#include <user.h>
#include <iostream>
#include <fstream>
#include <id.h>

User::User()
	: id(IDGenerator::getInstance()->getNextID())
	, name("")
	, email("")
	, password("")
	, address("")
	, phoneNumber("")
{
}

User::User(const std::string &name, const std::string &email,
	   const std::string &password)
	: id(IDGenerator::getInstance()->getNextID())
	, name(name)
	, email(email)
	, password(password)
{
}

User::~User()
{
}

void User::updateProfile(const std::string &name, const std::string &email,
			 const std::string &address,
			 const std::string &phoneNumber)
{
	this->name = name;
	this->email = email;
	this->address = address;
	this->phoneNumber = phoneNumber;
}

void User::changePassword(const std::string &newPassword)
{
	this->password = newPassword;
}

void User::addToCart(const std::shared_ptr<Product> &product, long long quantity)
{
	cart.addProduct(product, quantity);
}

void User::removeFromCart(const long long productId)
{
	cart.removeProduct(productId);
}

void User::addToWishlist(const std::shared_ptr<Product> &product, long long quantity)
{
	wishlist.addProduct(product, quantity);
}

void User::removeFromWishlist(const long long productId)
{
	wishlist.removeProduct(productId);
}

void User::clearCart()
{
	cart.clearCart();
}

double User::getTotalPrice() const
{
	return cart.totalPrice();
}
size_t User::getCartSize() const
{
	return cart.getCartSize();
}

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

const std::string &User::getName() const
{
	return this->name;
}

const std::string &User::getEmail() const
{
	return this->email;
}

const std::string &User::getAddress() const
{
	return this->address;
}

const std::string &User::getPhoneNumber() const
{
	return this->phoneNumber;
}

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