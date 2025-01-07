#ifndef __ALTERNATIVE_VISITOR_H__
#define __ALTERNATIVE_VISITOR_H__

#include <variant>
#include <products/book.h>
#include <products/clothing.h>
#include <products/electronics.h>
#include <products/furniture.h>
#include <products/sports.h>

// Type-safe visitor using std::variant
using ProductVariant = std::variant<
    std::reference_wrapper<const Book>,
    std::reference_wrapper<const Clothing>,
    std::reference_wrapper<const Electronics>,
    std::reference_wrapper<const Furniture>,
    std::reference_wrapper<const Sports>
>;

// Example visitor that calculates insurance values
class InsuranceValueCalculator {
    static constexpr double BOOK_RATE = 0.1;      // 10% of price
    static constexpr double CLOTHING_RATE = 0.2;   // 20% of price
    static constexpr double ELECTRONICS_RATE = 0.3; // 30% of price
    static constexpr double FURNITE_RATE = 0.5;     // 50% of price
    static constexpr double SPORTS_RATE = 0.2;     // 20% of price

public:
    double operator()(const std::reference_wrapper<const Book>& book) const {
        return book.get().getPrice() * BOOK_RATE;
    }

    double operator()(const std::reference_wrapper<const Clothing>& clothing) const {
        return clothing.get().getPrice() * CLOTHING_RATE;
    }

    double operator()(const std::reference_wrapper<const Electronics>& electronics) const {
        return electronics.get().getPrice() * ELECTRONICS_RATE;
    }
    
    double operator()(const std::reference_wrapper<const Furniture>& furniture) const {
        return furniture.get().getPrice() * FURNITE_RATE;
    }

    double operator()(const std::reference_wrapper<const Sports>& sports) const {
        return sports.get().getPrice() * SPORTS_RATE;
    }
};

// Example visitor that generates marketing descriptions
class MarketingDescriptionGenerator {
public:
    std::string operator()(const std::reference_wrapper<const Book>& book) const {
        return "Bestselling book by " + book.get().getAuthor();
    }

    std::string operator()(const std::reference_wrapper<const Clothing>& clothing) const {
        return "Fashion-forward clothing piece";
    }

    std::string operator()(const std::reference_wrapper<const Electronics>& electronics) const {
        return "High-tech electronic device with " + electronics.get().getBrand();
    }

    std::string operator()(const std::reference_wrapper<const Furniture>& furniture) const {
        return "Furniture from the future";
    }

    std::string operator()(const std::reference_wrapper<const Sports>& sports) const {
        return "Innovative sports equipament that will change your life";
    }
};

#endif
