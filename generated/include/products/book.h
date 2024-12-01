#ifndef __BOOKS_H__
#define __BOOKS_H__
#include "products/product.h"
#include <sstream>

class Book: public Product {
    std::string author;
    std::string publisher;
    std::string isbn;
public:
    Book(size_t id, const std::string &name, const std::string &description,
         double price, double weight, const std::string &manufacturer,
         const Dimensions &dimensions, const std::string &author,
         const std::string &publisher, const std::string &isbn)
        : Product(id, name, description, price, weight, manufacturer, dimensions),
          author(author), publisher(publisher), isbn(isbn) {}
    const std::string &getAuthor() const { return author; }
    const std::string &getPublisher() const { return publisher; }
    const std::string &getISBN() const { return isbn; }
    std::string generateDescription() const override {
        std::stringstream ss;
        ss << Product::generateDescription();
        ss << "Author: " << author << '\n';
        ss << "Publisher: " << publisher << '\n';
        ss << "ISBN: " << isbn << '\n';
        return ss.str();
    }
    std::string getCategory() const override {
        static const std::string category = "Book";
        return category;
    }
};
#endif