#include <id.h>
#include <memory>
#include <stdio.h>
// Initialize the static member
std::unique_ptr<IDGenerator> IDGenerator::instance = nullptr;

IDGenerator* IDGenerator::getInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<IDGenerator>();
    }
    return instance.get();
}

size_t IDGenerator::getNextID() {
    return ++currentID;
}