#include <iostream>

#include "LargeNum.h"

int main() {
    LargeNum a("2.222");
    LargeNum b("0");

    std::cout <<a/b<< std::endl;
    return 0;
}
