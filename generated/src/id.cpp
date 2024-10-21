#include <id.h>

// Initialize the static member
IDGenerator* IDGenerator::instance = nullptr;

IDGenerator* IDGenerator::getInstance() {
    if (instance == nullptr) {
        instance = new IDGenerator();
    }
    return instance;
}

size_t IDGenerator::getNextID() {
    return ++currentID;
}

void IDGenerator::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
    }
}