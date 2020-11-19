#include "Fraction.h"
#include "Interaction.h"

int main(int argc, char** argv) {
    Interaction<Fraction> *interaction = new Interaction<Fraction>("MY HOMEWORK T2");
    interaction->Run();
    delete interaction;
    return 0;
}