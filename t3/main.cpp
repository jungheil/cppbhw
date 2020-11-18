#include <iostream>

#include "LargeNum.h"
#include "Interaction.h"

int main() {
    LargeNum a("135");
    LargeNum b("3");
    Formula<LargeNum> c;
    c.set_num1(a);
    c.set_num2(b);
    c.set_operator((INTERACTION_OPERATOR)4);
    std::cout <<a.Scientific()<< std::endl;
    return 0;
}
