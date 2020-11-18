#include <iostream>

#include "LargeNum.h"
#include "Interaction.h"

int main(int argc, char** argv) {
    Interaction<LargeNum> interaction("MY HOMEWORK T3");
    interaction.Run();
    return 0;
}
