#include <iostream>
#include <fstream>
#include "Bank.h"

using namespace std;

int main(int argc, char** argv){
    Bank bank("rate.csv");
    UI ui(&bank);
    ui.Run();
}
