//
// Created by jungh on 18/11/2020.
//
#include "Interaction.h"

#include <sstream>

using namespace std;

template <class T>
bool Formula<T>::Result(T &result){
    if(num1_.get_nan() || num2_.get_nan() || op_==OPERATOR_NONE){
        return false;
    }else {
        switch (op_){
            case OPERATOR_ADDITION:
                result = num1_ + num2_;
                break;
            case OPERATOR_SUBTRACTION:
                result = num1_ - num2_;
                break;
            case OPERATOR_MULTIPLICATION:
                result = num1_ * num2_;
                break;
            case OPERATOR_DIVISION:
                result = num1_ / num2_;
                break;
        }
        return true;
    }
}

template<class T>
std::string Formula<T>::PrintFormula(){
    stringstream ss;
    ss << num1_ << "\t";
    char sop;
    switch (op_){
        case OPERATOR_ADDITION:
            sop = '+';
            break;
        case OPERATOR_SUBTRACTION:
            sop = '-';
            break;
        case OPERATOR_MULTIPLICATION:
            sop = '*';
            break;
        case OPERATOR_DIVISION:
            sop = '/';
            break;
        default:
            sop = '?';
    }
    ss << sop << "\t";
    ss << num2_ << "\t";
    T result;
    if(Result(result)){
        ss << "=\t" << result << "\t";
    }else{
        ss << "=\t?\t";
    }
    return ss.str();
}

template <class T>
void Interaction<T>::Display() {
    stringstream ss;
    ss<<"==="<<name_<<"==="<<endl;

}