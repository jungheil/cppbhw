#include <iostream>

#include "LargeNum.h"
#include "Interaction.h"

int main() {
    LargeNum a("2.222");
    LargeNum b("0");
    Formula<LargeNum> c;
    //c.set_num1(a);
    c.set_num2(b);
    c.set_operator((INTERACTION_OPERATOR)1);
    std::cout <<c.PrintFormula()<< std::endl;
    return 0;
}
