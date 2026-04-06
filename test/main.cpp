#include <iostream>

#include "Tests.h"

int main() {
    std::cout << "Running tests..." << std::endl;
    Tests::testAll();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
