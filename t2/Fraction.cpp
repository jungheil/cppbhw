//
// Created by jungh on 16/11/2020.
//

#include "Fraction.h"

#include <sstream>

Fraction::Fraction(int numerator, int denominator):
        numerator_(numerator), denominator_(denominator) {
    if(denominator == 0){
        nan_ = true;
    }
    Simplify();
}

Fraction::Fraction(std::string fraction){
    std::stringstream ss;
    ss.str("0" );
    bool flag=true;
    for(const auto &s: fraction){
        if (s == ' ') continue;
        else if (s == '/' && flag){
            ss >> numerator_;
            ss.clear();
            flag = !flag;
        }else if(s > 47 && s < 58){
            ss << s;
        }else{
            nan_ = true;
            return;
        }
    }
    if(flag){
        ss >> numerator_;
        denominator_ = 1;
    }else{
        ss >> denominator_;
        if(denominator_ == 0) nan_ = true;
        Simplify();
    }
}

std::ostream& operator << (std::ostream& out, const Fraction& fraction){
    if(fraction.nan_){
        out << "nan";
    }else if(fraction.numerator_ == 0) {
        out << 0;
    }else if(fraction.denominator_ == 1) {
        out << fraction.numerator_;
    }else{
        out << fraction.numerator_ << "/" <<fraction.denominator_;
    }
    return out;
}

std::istream& operator >> (std::istream& in, Fraction& fraction){
    std::string str;
    in >> str;
    fraction = Fraction(str);
    return in;
}

Fraction operator + (Fraction a, Fraction b){
    if (a.nan_ || b.nan_) return Fraction();
    else return Fraction(a.numerator_*b.denominator_+b.numerator_*a.denominator_,
                         a.denominator_*b.denominator_);
}

Fraction operator - (Fraction a, Fraction b){
    if (a.nan_ || b.nan_) return Fraction();
    else return Fraction(a.numerator_*b.denominator_-b.numerator_*a.denominator_,
                         a.denominator_*b.denominator_);
}

Fraction operator * (Fraction a, Fraction b){
    if (a.nan_ || b.nan_) return Fraction();
    else return Fraction(a.numerator_*b.numerator_, a.denominator_*b.denominator_);
}

Fraction operator / (Fraction a, Fraction b){
    if (a.nan_ || b.nan_) return Fraction();
    else return Fraction(a.numerator_*b.denominator_, a.denominator_*b.numerator_);
}

int Fraction::Gcd(int a, int b) {
    if(abs(a) < abs(b)) std::swap(a,b);
    return b==0 ? a: Gcd(b, a%b);
}

void Fraction::Simplify(){
    int gcd = Gcd(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;

    if(denominator_ < 0){
        denominator_ = -denominator_;
        numerator_ = -numerator_;
    }
}