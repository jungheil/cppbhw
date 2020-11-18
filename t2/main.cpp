#include <iostream>
#include <vector>
#include "Fraction.h"
#include <sstream>
int main(int argc, char** argv) {
    Fraction a(4,2);
    Fraction b(0,100);
    //std::cin >> a;
    std::vector<int> dd;
    dd.push_back(1);
    dd.push_back(2);
    //dd.push_back(3);

    std::cout<<dd.size()<<std::endl;
    return 0;
}