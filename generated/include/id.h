#ifndef __ID_H__
#define __ID_H__

#include <stdlib.h>

class IDGenerator {
private:
    static IDGenerator* instance;
    size_t currentID;

    // Private constructor to prevent instantiation
    IDGenerator() : currentID(0) {}

public:
    // Delete copy constructor and assignment operator
    IDGenerator(const IDGenerator&) = delete;
    IDGenerator& operator=(const IDGenerator&) = delete;

    static IDGenerator* getInstance();
    size_t getNextID();
};

#endif