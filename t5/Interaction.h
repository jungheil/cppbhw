//
// Created by jungh on 22/11/2020.
//

#ifndef T5_INTERACTION_H
#define T5_INTERACTION_H

#include "Company.h"

class Interaction{
public:
    Interaction();
    void Run();

private:
    void List();
    void SaveData();
    void AddEmployee();
    void DeleteEmployee();
    void ChangePosition();
    void SetBonus();
    void SetSales();

    Company* SelectDepartment(std::string name);

    bool RUSure(std::string name);
    void FalseReturn(std::string name, std::string type);

private:
    Company *company_;
    Administrative *administrative_;
    Technology *technology_;
    Market *market_;
};

#endif //T5_INTERACTION_H
