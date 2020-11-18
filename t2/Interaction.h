//
// Created by jungh on 18/11/2020.
//

#ifndef T3_INTERACTION_H
#define T3_INTERACTION_H

#include <iostream>
#include <sstream>
#include <vector>

#include "Fraction.h"

enum INTERACTION_OPERATOR{
    OPERATOR_NONE               =   0,
    OPERATOR_ADDITION           =   1,
    OPERATOR_SUBTRACTION        =   2,
    OPERATOR_MULTIPLICATION     =   3,
    OPERATOR_DIVISION           =   4
};

template<class T>
class Formula{
public:
    Formula() = default;
    void set_num1(const T &num){num1_ = num;};
    void set_num2(const T &num){num2_ = num;};
    void set_operator(INTERACTION_OPERATOR op){op_ = op;};
    bool Result(T &result) const;
    std::string PrintFormula() const;


private:
    //TODO 要不要变成指针？
    T num1_,num2_;
    INTERACTION_OPERATOR op_ = OPERATOR_NONE;
};

template<class T>
class Interaction{
public:
    Interaction(std::string name):name_(name){};
    void Display();
    void Run();

private:
    std::string name_;
    int MAX_HISTORY_ =10;
    std::vector<Formula<T>> formulas_;
    enum INTERACTION_STATE{
        INTERACTION_STATE_FIRST         =   0,
        INTERACTION_STATE_OPERATOR      =   1,
        INTERACTION_STATE_SECOND        =   2
    };
};

template class Formula<Fraction>;
template class Interaction<Fraction>;

#endif //T3_INTERACTION_H
