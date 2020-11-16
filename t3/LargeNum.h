//
// Created by jungh on 15/11/2020.
//

#ifndef T3_LARGENUM_H
#define T3_LARGENUM_H

#include <map>
#include <utility>

// 用于格式化用户输入的大数
class FormatNum{
public:
    FormatNum(){
        states_[0]['-'] = 1;
        states_[0]['d'] = 2;
        states_[0]['.'] = 3;
        states_[1]['d'] = 2;
        states_[1]['.'] = 3;
        states_[2]['d'] = 2;
        states_[2]['.'] = 3;
        states_[3]['d'] = 4;
        states_[4]['d'] = 4;
    };
    bool LookUpState(int &state, const char &s);

private:
    // 状态转移表
    std::map<char, int> states_[5];

};

// 大数类
class LargeNum{
public:
    LargeNum():nan_(true){};
    explicit LargeNum(std::string num);
    LargeNum(bool positive, std::string initer, std::string fractional = ""):
            positive_(positive), initer_(std::move(initer)), fractional_(std::move(fractional)){
        Simplify();
    };

    friend class CAddition;
    friend class CSubtraction;
    friend class CMultiplication;
    friend class CDivision;

    // 重载cout
    friend std::ostream& operator << (std::ostream&, const LargeNum&);

    friend std::istream& operator >> (std::istream&, LargeNum&);
    friend bool operator > (const LargeNum&,const LargeNum&);
    friend bool operator < (const LargeNum&,const LargeNum&);
    friend bool operator == (const LargeNum&,const LargeNum&);
    friend LargeNum operator - (const LargeNum&);
    friend LargeNum operator + (const LargeNum&, const LargeNum&);
    friend LargeNum operator - (const LargeNum&, const LargeNum&);
    friend LargeNum operator * (const LargeNum&, const LargeNum&);
    friend LargeNum operator / (const LargeNum&, const LargeNum&);

    friend LargeNum abs(const LargeNum &largenum);

private:
    void Simplify();


private:
    bool nan_ = false;
    bool positive_ = true;  // 符号
    bool decimals_ = false;  // 是否为小数
    std::string initer_;  // 整数部分
    std::string fractional_;  // 小数部分
    static FormatNum formatnum_;
};

// 大数计算基类
class Compute{
public:
    Compute() = default;
    virtual LargeNum Solve(const LargeNum &num1, const LargeNum &num2) = 0;

    static void BAddZero(std::string &num1, std::string &num2);
    static void FAddZero(std::string &num1, std::string &num2);
    static std::string SAddition(const std::string &num1, const std::string &num2, bool carry = false);
    static std::string SSubtraction(const std::string &num1, const std::string &num2, bool carry = false);
    static std::string SMultiplication(const std::string &num1, const char &num2);
    static std::string SDivision(std::string &num1, const std::string &num2);
};

class CAddition: public Compute{
public:
    LargeNum Solve(const LargeNum &num1, const LargeNum &num2) override;
    CAddition() = default;
};

class CSubtraction: public Compute{
public:
    CSubtraction() = default;
    LargeNum Solve(const LargeNum &num1, const LargeNum &num2) override;
};
class CMultiplication: public Compute{
public:
    CMultiplication() = default;
    LargeNum Solve(const LargeNum &num1, const LargeNum &num2) override;
};
class CDivision: public Compute{
public:
    CDivision() = default;
    LargeNum Solve(const LargeNum &num1, const LargeNum &num2) override;
};



#endif //T3_LARGENUM_H
