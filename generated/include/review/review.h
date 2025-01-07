#ifndef __REVIEW_H__
#define __REVIEW_H__

#include <string>
#include <ctime>
#include <stdexcept>

class Review {
    size_t userId;
    size_t productId;
    unsigned rating;  // 1-5 stars
    std::string comment;
    std::time_t timestamp;

public:
    Review(size_t userId, size_t productId, unsigned rating, const std::string& comment)
        : userId(userId), productId(productId), timestamp(std::time(nullptr)) {
        setRating(rating);
        setComment(comment);
    }

    void setRating(unsigned r) {
        if (r < 1 || r > 5) throw std::invalid_argument("Rating must be between 1 and 5");
        rating = r;
    }

    void setComment(const std::string& c) {
        if (c.length() > 1000) throw std::invalid_argument("Comment too long");
        comment = c;
    }

    // Getters
    unsigned getRating() const { return rating; }
    const std::string& getComment() const { return comment; }
    std::time_t getTimestamp() const { return timestamp; }
};

#endif
