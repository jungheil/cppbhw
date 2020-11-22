#include <iostream>
#include "Company.h"
#include "Interaction.h"

using namespace std;
int main(int argc, char** argv) {
    Interaction *interaction = new Interaction;
    interaction->Run();
    delete interaction;
}
