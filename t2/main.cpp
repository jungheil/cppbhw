#include <iostream>

#include "Fraction.h"
#include <sstream>
int main(int argc, char** argv) {
    Fraction a(4,2);
    Fraction b(0,100);
    std::cin >> a;

    std::cout<<a<<std::endl;
    return 0;
}