//
// Created by jungh on 16/11/2020.
//

#include "Fraction.h"

Fraction::Fraction(int numerator, int denominator):
        numerator_(numerator), denominator_(denominator) {
    if(denominator == 0){
        nan_ = true;
    }
    Simplify();
}

std::ostream& operator << (std::ostream& out, const Fraction& fraction){
    if(fraction.numerator_ == 0) {
        out << 0;
    }else if(fraction.denominator_ == 1) {
        out << fraction.numerator_;
    }else if(fraction.nan_){
        out << "nan";
    }else{
        out << fraction.numerator_ << "/" <<fraction.denominator_;
    }
    return out;
}

std::istream& operator >> (std::istream& in, Fraction& fraction){
    in >> fraction.numerator_ >> fraction.denominator_;
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
    else return Fraction(a.numerator_*b.denominator_, a.numerator_*b.denominator_);
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