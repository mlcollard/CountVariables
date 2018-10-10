/*
    variableCount_u.cpp

    Usage example of variableCount()
*/

#include <iostream>
#include "variableCount.hpp"

int main(int argc, const char* argv[]) {

    int count = variableCount(argv[1]);

    std::cout << count << '\n';

    return 0;
}
