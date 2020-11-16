//
// Created by jungh on 16/11/2020.
//

#ifndef T1_BANK_H
#define T1_BANK_H

#include <iostream>
#include <vector>

enum FACTORY_CURRENCY{
    FACTORY_CURRENCY_POUND		= 0,
    FACTORY_CURRENCY_EURO		= 1
};

class Bank{
public:
    Bank(std::string currency);
    double RMB2FC(double money) const;
    double FC2RMB(double money) const;
    const std::string &get_currency() const {return currency_;};
    double get_exchange_rate() const {return exchange_rate_;};

protected:
    std::string currency_;
    float exchange_rate_ = 1;

private:
    void SplitString(const std::string& s, std::vector<std::string>& tokens, char delim = ' ');
};

class Pound: public Bank{ ;
public:
    Pound():Bank("Pound"){}
};

class Euro: public Bank{
public:
    Euro():Bank("Euro"){};
};

class Factory{
public:
    Factory() = default;
    Bank *GetBank(FACTORY_CURRENCY index);
};

#endif //T1_BANK_H
