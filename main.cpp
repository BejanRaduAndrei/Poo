#include <user.h>
#include <cart/shoppingCart.h>
#include <products/product.h>
#include <products/book.h>
#include <products/electronics.h>
#include <products/clothing.h>
#include <iostream>
#include <fstream>
#include <id.h>
#include <random>
#include <assert.h>
#include <order.h>
#include <thread>
#include <payment/cardPayment.h>
#include <payment/cashPayment.h>
#include <payment/onlinePayment.h>
#include <pricing/priceCalculator.h>
#include <inventory/inventory.h>
#include <review/review.h>
#include <visitor/alternativeVisitor.h>

const std::string CARD_NUMBER = "ABCDEF1234567890"; 

void testAdding(User &user) {
    size_t prevLength = user.getCartSize();
    user.addToCart(std::make_unique<Product>(100, "Coffee", 10), 5);
    assert(user.getCartSize() == prevLength + 1);
}

void testRemoving(User &user) {
    size_t prevLength = user.getCartSize();
    user.removeFromCart(100);
    assert(user.getCartSize() == prevLength - 1);
}

void testClearing(User &user) {
    user.clearCart();
    assert(user.getCartSize() == 0);
}

void testTotalPrice(User &user) {
    double price = user.getTotalPrice();
    assert(price >= 0);
}

void testUser() {
    User user = User("John Doe", "", "");
    assert(user.getName() == "John Doe");
    assert(user.getEmail() == "");
    assert(user.getAddress() == "");
    assert(user.getPhoneNumber() == "");
    user.updateProfile("John Doe", "john.doe@gmail.com", "New York", "014124212421");
    assert(user.getName() == "John Doe");
    assert(user.getEmail() == "john.doe@gmail.com");
    assert(user.getAddress() == "New York");
    assert(user.getPhoneNumber() == "014124212421");
}

void testCopyConstructorShopping() {
    ShoppingCart cart;
    cart.addProduct(std::make_unique<Product>(100, "Coffee", 10), 5);
    ShoppingCart cart2(cart);
    assert(cart2.getCartSize() == 1);
}

void testCopyAssignmentShopping() {
    ShoppingCart cart;
    cart.addProduct(std::make_unique<Product>(100, "Coffee", 10), 5);
    ShoppingCart cart2;
    cart2 = cart;
    assert(cart2.getCartSize() == 1);
}

void testOrder(User &user, std::vector<std::shared_ptr<Product>> &p) {
    try {
        ShoppingCart cart;
        for(int i = 0; i < 5; ++i) {
            cart.addProduct(p.at(i), rand() % 5);
        }
        Order order = Order(1, user, cart);
        assert(order.getOrderId() == 1);
        order.handlePayment(std::make_unique<CardPayment>(CARD_NUMBER));
        assert(order.getStatus() == "Paid");
        order.handleRefund();
        assert(order.getStatus() == "Refunded");
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void testPayment() {
    try {
        CardPayment cardPayment(CARD_NUMBER);
        cardPayment.pay(100);
        cardPayment.refund();
        CashPayment cashPayment;
        cashPayment.pay(50);
        cashPayment.refund();
        OnlinePayment onlinePayment("john.doe@gmail.com");
        onlinePayment.pay(200);
        onlinePayment.refund();
        cardPayment.pay(1200);
    } catch (const std::exception& e) {
        if (const auto* invalidCard = dynamic_cast<const InvalidCardException*>(&e)) {
            std::cout << "Invalid card exception: " << invalidCard->what() << '\n';
        } else if (const auto* insufficientFunds = dynamic_cast<const InsufficientFundsException*>(&e)) {
            std::cout << "Insufficient funds exception: " << insufficientFunds->what() << '\n';
        } else if (const auto* paymentTimeout = dynamic_cast<const PaymentTimeoutException*>(&e)) {
            std::cout << "PaymentStrategy timeout exception: " << paymentTimeout->what() << '\n';
        } else {
            std::cout << "Unknown payment exception: " << e.what() << '\n';
        }
    }
}

void testDynamicCast(User& user, std::vector<std::shared_ptr<Product>>& p) {
    ShoppingCart cart;
    for(int i = 0; i < 2; ++i) {
        cart.addProduct(p.at(i), rand() % 2);
    }
    Order order = Order(1, user, cart);
    assert(order.getOrderId() == 1);
    try {
        order.handlePayment(std::make_unique<CardPayment>(CARD_NUMBER));
        order.processSpecificPayment();    
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void testShoppingCartExpiration() {
    ShoppingCart cart;
    auto product = std::make_shared<Product>(1, "Test Product", 10.0);
    cart.addProduct(product, 5);
    
    assert(!cart.isExpired()); // Should not be expired immediately
    
    // Force expiration by waiting (only in development)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    assert(cart.isExpired());
    
    cart.refreshExpiration(); // Reset expiration
    assert(!cart.isExpired()); // Should not be expired after refresh
    
    std::cout << "Shopping cart expiration test passed\n";
}

void testShoppingCartQuantityLimit() {
    ShoppingCart cart;
    auto product = std::make_shared<Product>(1, "Test Product", 10.0);
    
    // Test normal quantity
    try {
        cart.addProduct(product, 5);
        assert(cart.getCartSize() == 1);
    } catch (const std::exception&) {
        assert(false); // Should not throw
    }
    
    // Test exceeding quantity
    try {
        cart.addProduct(product, 15); // Should throw
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        assert(true); // Should catch quantity limit exception
    }
    
    std::cout << "Shopping cart quantity limit test passed\n";
}

void testWishlistPriceTracking() {
    WishlistCart wishlist;
    auto product = std::make_shared<Product>(1, "Test Product", "Original", 100.0, 1.0, "Test Corp", Dimensions{1,1,1});
    wishlist.addProduct(product, 1);
    
    std::vector<std::pair<size_t, double>> priceDrops;
    assert(!wishlist.checkPriceDrops(priceDrops)); // No price drops yet
    assert(priceDrops.empty());
    
    // Create a new product with same ID but 20% lower price
    auto discountedProduct = std::make_shared<Product>(1, "Test Product", "Discounted", 75.0, 1.0, "Test Corp", Dimensions{1,1,1});
    wishlist.addProduct(discountedProduct, 1); // This should update the existing product
    
    bool hasDrops = wishlist.checkPriceDrops(priceDrops);
    assert(hasDrops); // Should detect price drop
    assert(priceDrops.size() == 1);
    assert(priceDrops[0].first == 1); // Product ID
    assert(priceDrops[0].second == 75.0); // New price
    
    std::cout << "Wishlist price tracking test passed\n";
}

void testPriceCalculatorFeatures() {
    ShoppingCart cart;
    
    // Add test products
    auto product1 = std::make_shared<Product>(1, "Test Product 1", "Description", 100.0, 1.0, "Test Corp", Dimensions{1,1,1});
    auto product2 = std::make_shared<Product>(2, "Test Product 2", "Description", 200.0, 1.0, "Test Corp", Dimensions{1,1,1});
    
    cart.addProduct(product1, 2);
    cart.addProduct(product2, 2);
    
    PriceCalculator<ShoppingCart> calculator(cart, 0.19, 0.05);
    double subtotalBeforeBulk = calculator.calculateSubtotal() - calculator.calculateDiscount();  // Use pre-tax total
    
    double withBulk = calculator.calculatePreTaxTotal();  // Compare pre-tax totals
    std::cout << "Pre-tax Subtotal: " << subtotalBeforeBulk << ", With Bulk Discount: " << withBulk << std::endl;
    assert(withBulk < subtotalBeforeBulk); // Should be less due to bulk discount
    
    // Test product-specific discount
    calculator.addProductDiscount(1, 0.20); // 20% off product 1
    assert(calculator.calculateProductPrice(1) == 80.0);
    
    auto discounted = calculator.getDiscountedProducts();
    assert(discounted.size() == 1);
    assert(discounted[0].first == 1);
    assert(discounted[0].second == 0.20);
}

void testReviewSystem() {
    auto product = std::make_shared<Product>(1, "Test Product", "Description", 100.0, 1.0, "Test Corp", Dimensions{1,1,1});
    
    // Test adding reviews
    Review review1(1, product->getID(), 5, "Great product!");
    Review review2(2, product->getID(), 3, "Average product");
    
    product->addReview(review1);
    assert(product->getAverageRating() == 5.0);
    assert(product->getReviewCount() == 1);
    
    product->addReview(review2);
    assert(product->getAverageRating() == 4.0);
    assert(product->getReviewCount() == 2);
    
    std::cout << "Review system test passed\n";
}

void testInventorySystem() {
    Inventory inventory;
    size_t productId = 1;
    
    // Test adding stock
    inventory.addStock(productId, 10);
    
    // Test reorder level
    inventory.setReorderLevel(productId, 5);
    assert(!inventory.needsReorder(productId));
    
    // Test removing stock
    inventory.removeStock(productId, 6);
    assert(inventory.needsReorder(productId));
    
    // Test insufficient stock
    try {
        inventory.removeStock(productId, 10);
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        assert(true);
    }
    
    std::cout << "Inventory system test passed\n";
}

void testLoyaltySystem(User& user) {
    assert(user.getLoyaltyPoints() == 0);
    assert(user.getLoyaltyDiscount() == 0.0);
    
    // Add points for a $100 purchase
    user.addLoyaltyPoints(100.0);
    assert(user.getLoyaltyPoints() == 1000); // 10 points per dollar
    assert(user.getLoyaltyDiscount() == 0.05); // Should now get 5% discount
    
    std::cout << "Loyalty system test passed\n";
}

void testAlternativeVisitor() {
    // Create test products
    auto book = std::make_shared<Book>(1, "The Great Gatsby", "Classic novel", 29.99, 0.5,
        "Scribner", Dimensions{20, 13, 2}, "F. Scott Fitzgerald", "Scribner", "978-0743273565");
    
    auto electronics = std::make_shared<Electronics>(2, "Smartphone", "High-end phone", 999.99, 0.3,
        "TechCo", Dimensions{15, 7, 1}, "12 months", "Samsung", "ABC123");
    
    auto clothing = std::make_shared<Clothing>(3, "T-Shirt", "Cotton T-Shirt", 19.99, 0.2,
        "Fashion Brand", Dimensions{30, 20, 2}, "M", "Cotton", "Blue");

    // Create visitors
    InsuranceValueCalculator insuranceCalc;
    MarketingDescriptionGenerator marketingGen;

    // Create variants
    std::vector<ProductVariant> products = {
        std::cref(*book),
        std::cref(*electronics),
        std::cref(*clothing)
    };

    // Test insurance calculations
    for (const auto& product : products) {
        double insurance = std::visit(insuranceCalc, product);
        assert(insurance > 0.0); // Insurance should be positive
    }

    // Test marketing descriptions
    for (const auto& product : products) {
        std::string desc = std::visit(marketingGen, product);
        assert(!desc.empty()); // Description shouldn't be empty
    }

    // Specific tests
    double bookInsurance = std::visit(insuranceCalc, products[0]);
    assert(bookInsurance == book->getPrice() * 0.1); // 10% for books

    double electronicsInsurance = std::visit(insuranceCalc, products[1]);
    assert(electronicsInsurance == electronics->getPrice() * 0.3); // 30% for electronics

    std::cout << "Alternative visitor pattern test passed\n";
}

void testOrderDiscounts(User& user) {
    // Create a test order
    ShoppingCart cart;
    auto product = std::make_shared<Product>(1, "Test Product", "Description", 100.0, 1.0, "Test Corp", Dimensions{1,1,1});
    cart.addProduct(product, 1);
    
    Order order(1, user, cart);
    
    // Create different types of discounts
    SeasonalDiscount winterSale(0.2);  // 20% off
    LoyaltyDiscount loyaltyDiscount;
    
    // Test individual discounts
    double withSeasonal = order.applyDiscount(winterSale);
    assert(withSeasonal == 80.0);  // 20% off 100
    
    // Add some loyalty points and test loyalty discount
    user.addLoyaltyPoints(100.0);  // Should give 5% discount
    double withLoyalty = order.applyDiscount(loyaltyDiscount);
    assert(withLoyalty == 95.0);  // 5% off 100
    
    // Test applying multiple discounts
    double withBoth = order.applyDiscounts(winterSale, loyaltyDiscount);
    assert(withBoth < withSeasonal && withBoth < withLoyalty && withBoth == 76);
    
    std::cout << "Order discount template test passed\n";
}

int main() {
    try {
        // Read products from input
        std::ifstream in("tastatura.txt");
        
        auto products = Product::readProductsFromInput(in);
        
        // Create user and add products
        User user("John Doe", "john@example.com", "password123");
        user.addToCart(products[0], 2);        // Add book
        user.addToCart(products[1], 1);        // Add smartphone
        user.addToWishlist(products[2], 1);    // Add t-shirt to wishlist
        testTotalPrice(user);

        // Use PriceCalculator for shopping cart
        ShoppingCart& userCart = user.getCart();
        PriceCalculator<ShoppingCart> cartCalculator(userCart, 0.19, 0.1); // 19% tax, 10% discount

        // Display cart summary
        std::cout << "\n=== Shopping Cart Summary ===\n";
        std::cout << "Subtotal: $" << cartCalculator.calculateSubtotal() << std::endl;
        std::cout << "Tax (19%): $" << cartCalculator.calculateTax() << std::endl;
        std::cout << "Discount (10%): $" << cartCalculator.calculateDiscount() << std::endl;
        std::cout << "Final Total: $" << cartCalculator.calculateTotal() << std::endl;

        // Process order
        Order order(1, user, userCart);
        order.handlePayment(std::make_unique<CardPayment>("1234567890123456"));
        order.processSpecificPayment();

        // Display wishlist
        std::cout << "\n=== Wishlist Items ===\n";
        std::cout << "Number of items: " << user.getWishlistSize() << std::endl;

        std::cout << "\n=== Testing Original Features ===\n";
        // Run tests
        testUser();
        testAdding(user);
        testRemoving(user);
        testClearing(user);
        testCopyConstructorShopping();
        testCopyAssignmentShopping();
        
        testOrder(user, products);
        testPayment();
        testDynamicCast(user, products);

        std::cout << "\n=== Testing New Features ===\n";
        testShoppingCartExpiration();
        testShoppingCartQuantityLimit();
        testWishlistPriceTracking();
        testPriceCalculatorFeatures();

        std::cout << "\n=== Testing Additional Systems ===\n";
        testReviewSystem();
        testInventorySystem();
        testLoyaltySystem(user);

        // Show loyalty status in cart summary
        std::cout << "\n=== Updated Cart Summary with Loyalty ===\n";
        std::cout << "Loyalty Points: " << user.getLoyaltyPoints() << std::endl;
        std::cout << "Loyalty Discount: " << (user.getLoyaltyDiscount() * 100) << "%" << std::endl;

        std::cout << "\n=== Testing Alternative Visitor Pattern ===\n";
        testAlternativeVisitor();

        std::cout << "\n=== Testing Order Discounts ===\n";
        testOrderDiscounts(user);

        std::cout << "\nAll tests passed successfully!\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}