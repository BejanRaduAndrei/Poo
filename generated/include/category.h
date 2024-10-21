#ifndef __CATEGORY_H__
#define __CATEGORY_H__

enum Category {
    ELECTRONICS,
    CLOTHINGS,
    BOOKS,
    TOYS,
    GROCERIES,
    FURNITURES,
    SPORTS,
    AUTOMOTIVES,
    UNKNOWN
};

const std::string& categoryToString(Category category);
Category stringToCategory(const std::string& categoryStr);
#endif