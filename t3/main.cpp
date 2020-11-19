#include <iostream>

#include "LargeNum.h"
#include "Interaction.h"

int main(int argc, char** argv) {
    Interaction<LargeNum> *interaction = new Interaction<LargeNum>("MY HOMEWORK T3");
    interaction->Run();
    delete interaction;
    return 0;
}
