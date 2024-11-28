#ifndef __ID_H__
#define __ID_H__

#include <stdlib.h>
#include <memory>

class IDGenerator {
private:
    static std::unique_ptr<IDGenerator> instance;
    size_t currentID;

public:
    IDGenerator() : currentID(0) {}
    // Delete copy constructor and assignment operator
    IDGenerator(const IDGenerator&) = delete;
    IDGenerator& operator=(const IDGenerator&) = delete;

    static IDGenerator* getInstance();
    size_t getNextID();
};

#endif