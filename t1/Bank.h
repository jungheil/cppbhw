//
// Created by jungh on 16/11/2020.
//

#ifndef T1_BANK_H
#define T1_BANK_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// 货币类
class Currency{
public:
    Currency(std::string name, float exchange_rate):name_(std::move(name)), exchange_rate_(exchange_rate){};
    double RMB2FC(double money) const;
    double FC2RMB(double money) const;
    const std::string& get_name() const {return name_;};
    double get_exchange_rate() const {return exchange_rate_;};

protected:
    std::string name_;
    float exchange_rate_ = 1;

};

// 银行类
class Bank{
public:
    explicit Bank(string path);
    const Currency* Get(string name);
    const Currency* Get(int index);
    int get_size() const {return size_;};
    const vector<Currency>& get_all(){return currency_;};


private:
    vector<Currency> currency_;
    int size_;
};

// 交互界面
class UI{
public:
    UI(Bank *bank):bank_(bank){};
    void Run();

private:
    void ChoiceCurrency(string);
    void Exchange(string);

private:
    enum EXCHANGE_TYPE{
        EXCHANGE_TYPE_FC2RMB        =   0,
        EXCHANGE_TYPE_RMB2FC        =   1
    };
    EXCHANGE_TYPE exchange_type_;
    Bank *bank_ = nullptr;
    const Currency *currency_ = nullptr;
};


#endif //T1_BANK_H
