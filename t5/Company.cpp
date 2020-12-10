//
// Created by jungh on 19/11/2020.
//

#include "Company.h"

#include <fstream>
#include <sstream>
#include <utility>
//#include <conio.h>


using namespace std;

int Company::index_ = 0;

Company::Company(std::string name, std::string employee_path):
co_name_(std::move(name)) {
    stringstream ss;
    string temp;
    ifstream fs(employee_path);
    getline(fs, temp);
    string department, index, p_name, level, position, salary;
    int i_index;
    while(getline(fs, temp)){
        ss.clear();
        ss.str("");
        ss<<temp;
        getline(ss ,department, ',');
        if(department != co_name_) continue;
        getline(ss ,index, ',');
        getline(ss ,p_name, ',');
        getline(ss ,level, ',');
        getline(ss ,position, ',');
        getline(ss ,salary, ',');
        i_index = stoi(index);
        employees_.push_back(new People(this,
                                        i_index,p_name,
                                        stoi(level),position,
                                        stof(salary)));
        if(i_index>index_) index_ = i_index;
    }
    fs.close();
}

Company::~Company() {
    for(People *p:employees_){
        delete p;
    }
    for(Company* c:departments_){
        delete c;
    }
}

bool Company::RemoveDepartment(Company *department) {
    bool ret;
    int i=0;
    for(Company *c:departments_){
        if(department==c) {
            delete c;
            ret = true;
            break;
        }
        i++;
    }
    if(ret){
        employees_[i]=employees_.back();
        employees_.pop_back();
        return true;
    }
    return false;
}

std::vector<People*> Company::ListEmployee() const{
    std::vector<People*> out, temp;
    out.insert(out.end(), employees_.begin(), employees_.end());
    for(Company *c:departments_){
        temp = c->ListEmployee();
        out.insert(out.end(), temp.begin(), temp.end());
    }
    return out;
}

bool Company::AddEmployee(People *people, const std::string& position) {
    if(!ChangePosition(people,position)) return false;
    people->index_ = ++index_;
    people->department_ = this;
    people->salary_=CalculateSalary(people);
    employees_.push_back(people);
    return true;
}

bool Company::RemoveEmplyee(People *people) {
    bool ret;
    int i=0;
    for(People *p:employees_){
        if(people==p) {
            delete p;
            ret = true;
            break;
        }
        i++;
    }
    if(ret){
        employees_[i]=employees_.back();
        employees_.pop_back();
        return true;
    }
    return false;
}

// TODO 判断此人是不是这个部门
bool Company::ChangePosition(People *people, const std::string& position) {
    int level;
    try {
        level = positions_.at(position);
    } catch (std::exception& e) {
        return false;
    }
    people->level_ = level;
    people->position_=position;
    people->salary_=CalculateSalary(people);
    return true;
}

void Company::SaveData(std::string path) const {
    std::vector<People*> people = ListEmployee();

    ofstream fs(path, ios::out);
    fs << "department,index,name,level,position,salary" <<endl;
    for(const auto s:people){
        fs<<s->get_department()->get_co_name()<<','<<s->get_index()<<','<<s->get_name()<<','
            <<s->get_level()<<','<<s->get_position()<<','<<s->get_salary_()<<endl;
    }
    fs.close();
}

void Company::UpdateSalary() {
    for(auto p:employees_){
        p->salary_=this->CalculateSalary(p);
    }
    for(auto c:departments_){
        for(auto p:c->employees_){
            p->salary_=c->CalculateSalary(p);
        }
    }
}

Administrative::Administrative():Company("Administrative") {
    positions_ = {
            {"General manager", 4}
    };
}

Administrative::Administrative(std::string employee_path, std::string config_path):
Company("Administrative", std::move(employee_path)) {
    positions_ = {
            {"General manager", 4}
    };
}

float Administrative::CalculateSalary(People *people) {
    if (people->get_position() == "General manager"){
        return 20000;
    }else{
        return 0;
    }
}

Technology::Technology():Company("Technology") {
    positions_ = {
            {"Technical manager", 3},
            {"Technical staff" , 2}
    };
}

Technology::Technology(std::string employee_path, std::string config_path):
Company("Technology", std::move(employee_path)) {
    string temp;
    stringstream ss;
    ifstream fs(config_path);
    getline(fs, temp);
    while(getline(fs, temp)){
        ss.clear();
        ss.str("");
        ss<<temp;
        getline(ss ,temp, ',');
        if(temp != co_name_) continue;
        getline(ss ,temp, ',');
        bonus_ = stof(temp);
        break;
    }
    fs.close();

    positions_ = {
            {"Technical manager", 3},
            {"Technical staff" , 2}
    };
}

float Technology::CalculateSalary(People *people) {
    if (people->get_position() == "Technical manager"){
        return 12000 + bonus_;
    }else if(people->get_position() == "Technical staff"){
        return 6000 + bonus_;
    }else{
        return 0;
    }
}

void Technology::set_bonus(float bonus) {
    bonus_ = bonus;
    UpdateSalary();
}

Market::Market():Company("Market") {
    positions_ = {
            {"Sales manager", 3},
            {"Salesperson" , 1}
    };
}

Market::Market(std::string employee_path, std::string config_path):
Company("Market", std::move(employee_path)) {
    string temp;
    stringstream ss;
    ifstream fs(config_path);
    getline(fs, temp);
    while(getline(fs, temp)){
        ss.clear();
        ss.str("");
        ss<<temp;
        getline(ss ,temp, ',');
        if(temp != co_name_) continue;
        getline(ss ,temp, ',');
        sales_ = stof(temp);
        break;
    }
    fs.close();

    positions_ = {
            {"Sales manager", 3},
            {"Salesperson" , 1}
    };
}

float Market::CalculateSalary(People *people) {
    if (people->get_position() == "Sales manager"){
        return 8000 + sales_ * 0.005f;
    }else if(people->get_position() == "Salesperson"){
        return sales_ * 0.01f;
    }else{
        return 0;
    }
}

void Market::set_sales(float sales) {
    sales_ = sales;
    UpdateSalary();
}

