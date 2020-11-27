//
// Created by jungh on 16/11/2020.
//

#ifndef T2_FRACTION_H
#define T2_FRACTION_H

#include <iostream>

// 分数类
class Fraction{
public:
    // 无参构造的分数为nan
    Fraction():nan_(true){};
    // 输入分子和分母构造
    Fraction(int numerator, int denominator = 1);
    // 使用字符串构造
    Fraction(std::string fraction);
    bool get_nan() const{return nan_;};

    // 重载运算符
    friend std::ostream& operator << (std::ostream&, const Fraction&);
    friend std::istream& operator >> (std::istream&, Fraction&);

    friend Fraction operator + (Fraction, Fraction);
    friend Fraction operator - (Fraction, Fraction);
    friend Fraction operator * (Fraction, Fraction);
    friend Fraction operator / (Fraction, Fraction);


private:
    // 计算最大公约数，化简用
    int Gcd(int a, int b);
    // 化简分数
    void Simplify();

private:
    int numerator_;
    int denominator_;
    bool nan_ = false;

};


#endif //T2_FRACTION_H
