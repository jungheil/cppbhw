#include <iostream>

#include "Bank.h"

using namespace std;

int main(int argc, char** argv){
    Factory factory;
    Bank *bank = factory.GetBank(FACTORY_CURRENCY_POUND);
    cout<<bank->RMB2FC(8)<<endl;
    delete bank;
    bank = NULL;
}
