//
// Created by jungh on 18/11/2020.
//
#include "Interaction.h"

#include <sstream>
#include <windows.h>

using namespace std;

template <class T>
bool Formula<T>::Result(T &result) const{
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
std::string Formula<T>::PrintFormula() const{
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
    ss<<"=================================================="<<endl;
    if(formulas_.size()<MAX_HISTORY_){
        for(int i=0; i<MAX_HISTORY_-formulas_.size(); i++){
            ss<<"->"<<endl;
        }
    }
    for(const auto& s: formulas_){
        ss<<"->\t"<<s.PrintFormula()<<endl;
    }
    ss<<"--------------------------------------------------"<<endl;
    //ss<<"input: "<<endl;
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<name_<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();
}

template <class T>
void Interaction<T>::Run() {
    T num;
    T last;
    INTERACTION_STATE state = INTERACTION_STATE_FIRST;
    Formula<T> formula;

    while(true){
        Display();
        cout << ">>\t" << formula.PrintFormula()<<endl;
        cout<<"--------------------------------------------------"<<endl;
        switch (state) {
            case INTERACTION_STATE_FIRST:
                cout<<"Please input the first NUMBER: "<<endl;
                cout<<"(You can also input `exit` and `clear`)"<<endl;
                break;
            case INTERACTION_STATE_OPERATOR:
                cout<<"Please input the OPERATOR: "<<endl;
                cout<<"(You can also input `exit` and `clear`)"<<endl;
                break;
            case INTERACTION_STATE_SECOND:
                cout<<"Please input the second NUMBER: "<<endl;
                cout<<"(You can also input `exit` and `clear`)"<<endl;
                break;
        }

        stringstream ss;
        ss.clear();
        string stemp;

        cin >> stemp;
        ss << stemp;

        if(ss.str() == "exit"){
            break;
        }else if(ss.str() == "clear"){
            formula = Formula<T>();
            state = INTERACTION_STATE_FIRST;
        }

        switch (state){
            case INTERACTION_STATE_FIRST:
                ss >> num;
                if (num.get_nan()) break;
                formula.set_num1(num);
                state = INTERACTION_STATE_OPERATOR;
                break;
            case INTERACTION_STATE_OPERATOR:
                switch(ss.str()[0]){
                    case '+':
                        formula.set_operator(OPERATOR_ADDITION);
                        state = INTERACTION_STATE_SECOND;
                        break;
                    case '-':
                        formula.set_operator(OPERATOR_SUBTRACTION);
                        state = INTERACTION_STATE_SECOND;
                        break;
                    case '*':
                        formula.set_operator(OPERATOR_MULTIPLICATION);
                        state = INTERACTION_STATE_SECOND;
                        break;
                    case '/':
                        formula.set_operator(OPERATOR_DIVISION);
                        state = INTERACTION_STATE_SECOND;
                        break;
                }
                break;
            case INTERACTION_STATE_SECOND:
                ss >> num;
                if (num.get_nan()) break;
                formula.set_num2(num);
                if(formulas_.size() ==MAX_HISTORY_){
                    formulas_.erase(formulas_.begin());
                }
                formulas_.push_back(formula);
                formula.Result(last);
                formula = Formula<T>();
                if(last.get_nan())  state = INTERACTION_STATE_FIRST;
                else {
                    state = INTERACTION_STATE_OPERATOR;
                    formula.set_num1(last);
                }
                break;
        }
    }
}