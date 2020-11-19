#include <iostream>
#include <fstream>
#include "Bank.h"

using namespace std;

int main(int argc, char** argv){
    Bank *bank = new Bank("rate.csv");
    UI *ui = new UI(bank);
    ui->Run();
    delete ui;
    delete bank;
    return 0;
}
