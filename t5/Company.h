//
// Created by jungh on 19/11/2020.
//

#ifndef T5_COMPANY_H
#define T5_COMPANY_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>


class People{
public:
    explicit People(std::string name):name_(std::move(name)){};

    const std::string& get_name() const {return name_;};
    int get_index() const {return index_;};
    int get_level() const {return level_;};
    float get_salary_() const {return salary_;};
    const std::string& get_position() const {return position_;};
    const std::string& get_department() const {return department_;};

    friend class Company;

private:
    People(std::string department, int index, std::string name, int level, std::string position, float salary):
        department_(std::move(department)),index_(index),name_(std::move(name)),level_(level),position_(std::move(position)),salary_(salary){};

private:
    std::string name_;
    int index_ = -1;
    int level_ = 1;
    float salary_ = 0;
    std::string position_ = "None";
    std::string department_ = "None";
};

class Company{
public:
    explicit Company(std::string name):co_name_(std::move(name)){};
    Company(std::string name, std::string employee_path);
    ~Company();

    bool ChangePosition(People *people, const std::string& position);
    bool AddEmployee(People *people, const std::string& position);
    bool RemoveEmplyee(People *people);
    void AddDepartment(Company* department){departments_.push_back(department);};
    bool RemoveDepartment(Company* department);
    std::vector<People*> ListEmployee() const;

    void SaveData(std::string path) const;

    const std::map<std::string, int>& get_position(){return positions_;};

    void UpdateSalary();

    const std::string& get_co_name(){return co_name_;};

protected:
    virtual float CalculateSalary(People *people){return 10;};

protected:

    std::map<std::string, int> positions_;
    std::vector<Company*> departments_;
    std::vector<People*> employees_;

    static int index_;
    std::string co_name_;
};


// 公司各个部门，拥有不同计算工资的方法
class Administrative: public Company{
public:
    Administrative();
    explicit Administrative(std::string employee_path, std::string config_path);

protected:
    float CalculateSalary(People *people) override;
};

class Technology: public Company{
public:
    Technology();
    explicit Technology(std::string employee_path, std::string config_path);

    void set_bonus(float bonus);

protected:
    float CalculateSalary(People *people) override;

private:
    // 技术部的奖金
    float bonus_ = 0;
};

class Market: public Company{
public:
    Market();
    explicit Market(std::string employee_path, std::string config_path);

    void set_sales(float sales);
protected:
    float CalculateSalary(People *people) override;

private:
    float sales_ = 0;
};

inline bool CompareSalary(People* a, People* b){
    return a->get_salary_() < b->get_salary_();
}

#endif //T5_COMPANY_H
