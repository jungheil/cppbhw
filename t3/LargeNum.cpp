//
// Created by jungh on 15/11/2020.
//

#include "LargeNum.h"

#include <sstream>
#include <algorithm>
#include <vector>

//#include <iostream>

using namespace std;


bool FormatNum::LookUpState(int &state, const char &s) {
    char type;
    if(s <= '9' && s >= '0') type='d';
    else if (s == '.') type = '.';
    else if (s == '-') type = '-';
    else type = 'o';

    map<char, int>::iterator iter;
    iter = states_[state].find(type);
    if (iter == states_[state].end()){
        return false;
    }else {
        state = iter->second;
        return true;
    }
}

FormatNum LargeNum::formatnum_;

LargeNum::LargeNum(string num):nan_(false) {
    int state = 0;
    stringstream initer;
    stringstream fractional;
    // 判断用户输入合法性
    for (auto &s : num){
        if(formatnum_.LookUpState(state, s)){
            if(state == 1) positive_ = false;
            else if(state == 2) initer << s;
            else if(state == 4) fractional << s;
        }else{
            nan_ = true;
        }
    }
    initer_ = initer.str();
    fractional_ = fractional.str();
    Simplify();
}

void LargeNum::Simplify() {
    auto it = initer_.begin();
    while(*it == '0'){
        initer_.erase(it);
    }
    for(auto it = fractional_.rbegin(); it != fractional_.rend(); it++){
        if (*it == '0')  fractional_.erase(fractional_.end()-1);
        else break;
    }
    if (initer_.empty()) initer_ = "0";
    decimals_ = !fractional_.empty();
}

string LargeNum::Scientific() const{
    stringstream ss;
    int e;
    if(initer_ == "0"){
        if(!decimals_) return "0E0";
        int i=1;
        for(const auto &s: fractional_){
            if(s == '0') i++;
            else break;
        }
        e = -i;
        ss<<fractional_[i-1]<<'.'<<fractional_.substr(i,fractional_.size()-i)<<'E'<<e;
    }else{
        e = initer_.size()-1;
        ss<<initer_[0]<<'.'<<initer_.substr(1,initer_.size()-1)<<fractional_<<'E'<<e;
    }
    return ss.str();
}

void Compute::BAddZero(string &num1, string &num2){
    int diff = num1.size() - num2.size();
    if(diff == 0){
        return;
    }else if(diff > 0){
        for(int i = 0; i < diff; i++){
            num2 = num2 + "0";
        }
    }else{
        for(int i = 0; i < -diff; i++){
            num1 = num1 + "0";
        }
    }
}
void Compute::FAddZero(string &num1, string &num2){
    int diff = num1.size() - num2.size();
    if(diff == 0){
        return;
    }else if(diff > 0){
        for(int i = 0; i < diff; i++){
            num2 = "0" + num2;
        }
    }else{
        for(int i = 0; i < -diff; i++){
            num1 = "0" + num1;
        }
    }
}

string Compute::SAddition(const string &num1, const string &num2, bool carry) {
    stringstream ss;
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    while(it1 != num1.rend()){
        string temp = to_string((int)(*it1+*it2+carry - 96));
        if(temp.size()==1){
            ss << temp;
            carry = false;
        }else{
            ss << temp[1];
            carry = true;
        }
        it1++;it2++;
    }
    ss << (int)carry;
    string out;
    ss >> out;
    reverse(out.begin(),out.end());
    return out;
}

string Compute::SSubtraction(const string &num1, const string &num2, bool carry){
    stringstream ss;
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    while(it1 != num1.rend()){
        int temp = (int)(*it1-*it2-carry);
        if(temp<0){
            ss << to_string(temp+10);
            carry = true;
        }else{
            ss << to_string(temp);
            carry = false;
        }
        it1++;it2++;
    }
    ss << (int)carry;
    string out;
    ss >> out;
    reverse(out.begin(),out.end());
    return out;
}

string Compute::SMultiplication(const std::string &num1, const char &num2){
    char carry=0;
    stringstream ss;
    string temp;
    for(auto it = num1.rbegin(); it != num1.rend(); it++){
        temp = to_string((*it-48)*(num2-48)+carry);
        if(temp.size() == 1){
            ss << temp;
            carry = 0;
        }else{
            ss << temp[1];
            carry = temp[0]-48;
        }
    }
    ss << (char)(carry + 48);
    string out;
    ss >> out;
    reverse(out.begin(),out.end());
    return out;
}

std::string Compute::SDivision(std::string &num1, const std::string &num2){
    string out = "0";

    string tn;
    while(tn=num2,FAddZero(num1,tn),!(num1 < tn)){
        num1=SSubtraction(num1,tn);
        out[0]++;
    }
    return out;
}

std::ostream& operator << (std::ostream& out, const LargeNum& largenum){
    if (largenum.nan_){
        out << "nan";
    }else if(largenum.initer_=="0"&&
            largenum.decimals_){
        out<<largenum.Scientific();
    }else{
        out << (largenum.positive_?"":"-") << largenum.initer_;
        if(largenum.decimals_) out << '.' << largenum.fractional_;
    }
    return out;
}

std::istream& operator >> (std::istream& in, LargeNum& largenum){
    string str;
    in >> str;
    largenum = LargeNum(str);
    return in;
}

bool operator > (const LargeNum& num1,const LargeNum& num2){
    if(num1.nan_ || num2.nan_){
        perror("nan cannot be compared");
        exit(10);
    }
    if(!num1.positive_ && num2.positive_) return false;
    else if(num1.positive_ && !num2.positive_) return true;
    else{
        string n1 = num1.initer_;
        string n2 = num2.initer_;
        Compute::FAddZero(n1,n2);
        if(n1 > n2) return true;
        else if(n1 < n2) return false;
        else{
            n1 = num1.fractional_;
            n2 = num2.fractional_;
            Compute::BAddZero(n1,n2);
            return n1 > n2;
        }
    }
}
bool operator < (const LargeNum& num1,const LargeNum& num2){
    if(num1.nan_ || num2.nan_){
        perror("nan cannot be compared");
        exit(10);
    }
    if(!num1.positive_ && num2.positive_) return true;
    else if(num1.positive_ && !num2.positive_) return false;
    else{
        string n1 = num1.initer_;
        string n2 = num2.initer_;
        Compute::FAddZero(n1,n2);
        if(n1 > n2) return false;
        else if(n1 < n2) return true;
        else{
            n1 = num1.fractional_;
            n2 = num2.fractional_;
            Compute::BAddZero(n1,n2);
            return n1 < n2;
        }
    }

}
bool operator == (const LargeNum& num1,const LargeNum& num2){
    if(num1.nan_ || num2.nan_){
        perror("nan cannot be compared");
        exit(10);
    }
    return num1.initer_ == num2.initer_ && num1.fractional_ == num2.fractional_;
}

LargeNum abs(const LargeNum &largenum){
    LargeNum out(largenum);
    out.positive_ = true;
    return out;
}

LargeNum operator-(const LargeNum& largenum) {
    LargeNum out(largenum);
    out.positive_ = !out.positive_;
    return out;
}

LargeNum CAddition::Solve(const LargeNum &num1, const LargeNum &num2){
    if(num1.nan_||num2.nan_) return LargeNum();
    string n1_f;
    string n2_f;
    string n1_i;
    string n2_i;
    string out_f;
    string temp;
    bool carry = false;
    bool positive = true;
    if (num1.positive_ == num2.positive_){
        n1_i = num1.initer_;
        n2_i = num2.initer_;
        n1_f = num1.fractional_;
        n2_f = num2.fractional_;
        FAddZero(n1_i,n2_i);
        BAddZero(n1_f,n2_f);
        temp = SAddition(n1_f,n2_f);
        carry = temp[0]-48;
        temp.erase(temp.begin());
        out_f = temp;
        temp = SAddition(n1_i,n2_i,carry);
        return LargeNum(num1.positive_,temp,out_f);
    }else{
        if (num1.positive_) {
            if(num1 > abs(num2)){
                n1_i = num1.initer_;
                n2_i = num2.initer_;
                n1_f = num1.fractional_;
                n2_f = num2.fractional_;
            }else{
                positive = false;
                n1_i = num2.initer_;
                n2_i = num1.initer_;
                n1_f = num2.fractional_;
                n2_f = num1.fractional_;
            }
        }else{
            if(abs(num1) > num2){
                positive = false;
                n1_i = num1.initer_;
                n2_i = num2.initer_;
                n1_f = num1.fractional_;
                n2_f = num2.fractional_;
            }else{
                n1_i = num2.initer_;
                n2_i = num1.initer_;
                n1_f = num2.fractional_;
                n2_f = num1.fractional_;
            }
        }
        FAddZero(n1_i,n2_i);
        BAddZero(n1_f, n2_f);
        temp = SSubtraction(n1_f,n2_f);
        carry = temp[0]-48;
        temp.erase(temp.begin());
        out_f = temp;
        temp = SSubtraction(n1_i,n2_i,carry);
        temp.erase(temp.begin());
        return LargeNum(positive, temp, out_f);
    }
}


LargeNum CSubtraction::Solve(const LargeNum &num1, const LargeNum &num2){
    if(num1.nan_||num2.nan_) return LargeNum();
    CAddition add;
    return add.Solve(num1,-num2);
}

LargeNum CMultiplication::Solve(const LargeNum &num1, const LargeNum &num2){
    if(num1.nan_||num2.nan_) return LargeNum();
    int decimal_point = num1.fractional_.size()+num2.fractional_.size();
    string n1 = num1.initer_+num1.fractional_;
    string n2 = num2.initer_+num2.fractional_;
    string temp;
    vector<string> ns;
    int j=0;
    for(auto it=n2.rbegin(); it!=n2.rend(); it++){
        temp = SMultiplication(n1, *it);
        for(int i=0; i<j; i++){
            temp = temp+"0";
        }
        j++;
        ns.push_back(temp);
    }
    string out;
    for(auto n:ns){
        FAddZero(out,n);
        out = SAddition(out,n);
    }
    return LargeNum(!(num1.positive_^num2.positive_),
                    out.substr(0,out.size()-decimal_point),
                    out.substr(out.size()-decimal_point, decimal_point));
}

LargeNum CDivision::Solve(const LargeNum &num1, const LargeNum &num2){
    stringstream ss;
    if (num2.initer_=="0" && !num2.decimals_) return LargeNum();
    int nor = num2.fractional_.size()-num1.fractional_.size();
    string n1 = num1.initer_+num1.fractional_;
    string n2 = num2.initer_+num2.fractional_;
    if(nor < 0){
        for(int i=0;i< -nor;i++){
            n2 = n2 + "0";
        }
    }else{
        for(int i=0;i<nor;i++){
            n1 = n1 + "0";
        }
    }
    int slide = n1.size()-n2.size();
    BAddZero(n1,n2);
    int valid = 0;
    string temp;
    do{
        temp = SDivision(n1,n2);
        ss <<temp;
        n1 = n1 + "0";
        if(temp != "0" || valid != 0) valid++;
    }while(!(valid>2&&(int)ss.str().size() > slide+1+2||n1 == "0"));
    string out;
    ss >> out;

    if(out[out.size()-1]>'4') out[out.size()-2] ++;
    out.erase(out.end()-1);
    if(slide+1>0){
        return LargeNum(!(num1.positive_^num2.positive_),
                        out.substr(0,slide+1),
                        out.substr(slide+1,out.size()-slide-1));
    }else{
        for(int i = 0; i< -slide-1; i++){
            out = "0"+out;
        }
        return LargeNum(!(num1.positive_^num2.positive_),
                        "0",out);
    }
}

ComFactory comfactory;

LargeNum operator + (const LargeNum& num1, const LargeNum& num2){
    Compute *add = comfactory.Get('+');
    return add->Solve(num1,num2);
}

LargeNum operator - (const LargeNum& num1, const LargeNum& num2){
    Compute *sub = comfactory.Get('-');
    return sub->Solve(num1, num2);
}

LargeNum operator * (const LargeNum& num1, const LargeNum& num2){
    Compute *mul = comfactory.Get('*');
    return mul->Solve(num1, num2);
}

LargeNum operator / (const LargeNum& num1, const LargeNum& num2){
    Compute *div = comfactory.Get('/');
    return div->Solve(num1,num2);
}

ComFactory::~ComFactory(){
    if(caddition_ != nullptr) delete caddition_;
    if(csubtraction_ != nullptr) delete csubtraction_;
    if(cmultiplication_ != nullptr) delete cmultiplication_;
    if(cdivision_ != nullptr) delete cdivision_;
}

Compute* ComFactory::Get(char sym){
    switch(sym){
        case '+':
            if(caddition_ == nullptr) caddition_ = new CAddition;
            return caddition_;
            break;
        case '-':
            if(csubtraction_ == nullptr) csubtraction_ = new CSubtraction;
            return csubtraction_;
            break;
        case '*':
            if(cmultiplication_ == nullptr) cmultiplication_ = new CMultiplication;
            return cmultiplication_;
            break;
        case '/':
            if(cdivision_ == nullptr) cdivision_ = new CDivision;
            return cdivision_;
            break;
        default:
            return nullptr;
    }
}
