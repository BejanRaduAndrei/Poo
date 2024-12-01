#ifndef __PRODUCT_FACTORY_H__
#define __PRODUCT_FACTORY_H__

#include <memory>
#include "product.h"

class ProductFactory {
    static std::unique_ptr<ProductFactory> instance;
public:
    ProductFactory() = default;
    static ProductFactory* getInstance();
    std::shared_ptr<Product> createProduct(const std::string& category, size_t id, const std::string& name,
                                           const std::string& description, double price, double weight,
                                           const std::string& manufacturer, const Dimensions& dimensions,
                                           const std::string& extra1, const std::string& extra2, const std::string& extra3);
    std::shared_ptr<Product> createProduct(size_t id, const std::string& name,
                                           const std::string& description, double price, double weight,
                                           const std::string& manufacturer, const Dimensions& dimensions);
};

#endif