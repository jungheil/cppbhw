//
// Created by jungh on 15/11/2020.
//

#ifndef T3_LARGENUM_H
#define T3_LARGENUM_H

#include <map>

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
    LargeNum() = default;
    explicit LargeNum(std::string num);
    LargeNum(bool positive, std::string initer, std::string fractional = ""):
            nan_(false), positive_(positive), initer_(std::move(initer)), fractional_(std::move(fractional)){
        Simplify();
    };

    // 使用科学计数法显示
    std::string Scientific() const;
    bool get_nan() const{return nan_;};

    // 将计算类设置为友元
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
    // 化简（除0）
    void Simplify();


private:
    bool nan_ = true;
    bool positive_ = true;  // 符号
    bool decimals_ = false;  // 是否为小数
    std::string initer_;  // 整数部分
    std::string fractional_;  // 小数部分
    static FormatNum formatnum_;  // 状态转移
};

// 大数计算基类
class Compute{
public:
    Compute() = default;
    // 对外计算方法
    virtual LargeNum Solve(const LargeNum &num1, const LargeNum &num2) = 0;

    // 前补0和后补0
    static void BAddZero(std::string &num1, std::string &num2);
    static void FAddZero(std::string &num1, std::string &num2);
    // 按位加减乘除计算
    static std::string SAddition(const std::string &num1, const std::string &num2, bool carry = false);
    static std::string SSubtraction(const std::string &num1, const std::string &num2, bool carry = false);
    static std::string SMultiplication(const std::string &num1, const char &num2);
    static std::string SDivision(std::string &num1, const std::string &num2);
};

// 加减乘除计算子类
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

// 计算类的单例工厂
class ComFactory{
public:
    ComFactory() = default;
    ~ComFactory();
    Compute* Get(char sym);

private:
    CAddition *caddition_;
    CSubtraction *csubtraction_;
    CMultiplication *cmultiplication_;
    CDivision *cdivision_;
};


#endif //T3_LARGENUM_H
