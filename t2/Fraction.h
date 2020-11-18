//
// Created by jungh on 16/11/2020.
//

#ifndef T2_FRACTION_H
#define T2_FRACTION_H

#include <iostream>

class Fraction{
public:
    Fraction():nan_(true){};
    Fraction(int numerator, int denominator = 1);
    Fraction(std::string fraction);
    bool get_nan() const{return nan_;};

    friend std::ostream& operator << (std::ostream&, const Fraction&);
    friend std::istream& operator >> (std::istream&, Fraction&);

    friend Fraction operator + (Fraction, Fraction);
    friend Fraction operator - (Fraction, Fraction);
    friend Fraction operator * (Fraction, Fraction);
    friend Fraction operator / (Fraction, Fraction);


private:
    int Gcd(int a, int b);
    void Simplify();

private:
    int numerator_;
    int denominator_;
    bool nan_ = false;

};


#endif //T2_FRACTION_H
