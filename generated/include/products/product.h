#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <review/review.h>

struct Dimensions {
	float length;
	float width;
	float height;
};

class Product {
	size_t id;
	std::string name;
	std::string description;
	double price;
	double weight;
	std::string manufacturer;
	Dimensions dimensions;
	std::vector<Review> reviews;
	double averageRating{0.0};
	size_t totalReviews{0};

    public:
	Product(size_t, const std::string &, size_t);
	// Expected to be called when reading all the data about products
	// from a file or database
	Product(size_t, const std::string &, const std::string &, double,
		double, const std::string &, const Dimensions &);
	const size_t getID() const
	{
		return id;
	}
	const double getPrice() const
	{
		return price;
	}
	const double getWeight() const
	{
		return weight;
	}
	virtual std::string generateDescription() const;
	friend std::ostream &operator<<(std::ostream &os, const Product &obj);
	static std::vector<std::shared_ptr<Product> >
	readProductsFromInput(std::istream &ss);
	virtual std::string getCategory() const
	{
		return "Unknown";
	}
	void addReview(const Review& review) {
		reviews.push_back(review);
		updateAverageRating(review.getRating());
	}
	double getAverageRating() const { return averageRating; }
	size_t getReviewCount() const { return totalReviews; }

    private:
	void updateAverageRating(unsigned newRating) {
		averageRating = (averageRating * totalReviews + newRating) / (totalReviews + 1);
		totalReviews++;
	}
};

#endif