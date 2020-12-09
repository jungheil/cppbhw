//
// Created by jungh on 22/11/2020.
//

#include "Interaction.h"

#include <sstream>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

Interaction::Interaction() {
    company_ = new Company("Company");
    administrative_ = new Administrative("employee.csv","config.csv");
    technology_ = new Technology("employee.csv","config.csv");
    market_ = new Market("employee.csv","config.csv");
    company_->AddDepartment(administrative_);
    company_->AddDepartment(technology_);
    company_->AddDepartment(market_);
    company_->UpdateSalary();
}

void Interaction::Run() {
    char input;
    bool run = true;
    while(run){
        stringstream ss;
        ss<<"=================================================="<<endl;
        ss<<"* MENU"<<endl;
        ss<<"--------------------------------------------------"<<endl<<endl;
        ss<<"OPTIONS:"<<endl<<endl;
        ss<<"->  "<<"(1) List all employees(Salary ascending)."<<endl<<endl;
        ss<<"->  "<<"(2) Add employee."<<endl<<endl;
        ss<<"->  "<<"(3) Delete employee."<<endl<<endl;
        ss<<"->  "<<"(4) Set bonus."<<endl<<endl;
        ss<<"->  "<<"(5) Set sales."<<endl<<endl;
        ss<<"->  "<<"(6) Save data."<<endl<<endl;
        ss<<"->  "<<"(7) Exit."<<endl<<endl;
        ss<<"--------------------------------------------------"<<endl;

        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED|
                                BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
        cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        cout<<ss.str();

        input = getch();
        switch(input){
            case '1':
                List();
                break;
            case '2':
                AddEmployee();
                break;
            case '3':
                DeleteEmployee();
                break;
            case '4':
                SetBonus();
                break;
            case '5':
                SetSales();
                break;
            case '6':
                SaveData();
                break;
            case '7':
                run = false;
            case 27:
                run = false;
        }
    }
}

void Interaction::List() {
    float total;
    vector<People*> people = company_->ListEmployee();
    sort(people.begin(),people.end(),CompareSalary);
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* List all employees(Salary ascending)"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<setw(8)<<"-index"<<setw(17)<<"-name"<<setw(17)<<"-department"<<
            setw(8)<<"-level"<<setw(20)<<"-position"<<setw(11)<<"-salary"<<endl;
    for(const auto s:people){
        ss<<"->  "<<setw(8)<<s->get_index()<<setw(17)<<s->get_name()<<setw(17)<<s->get_department()
                <<setw(8)<<s->get_level()<<setw(20)<<s->get_position()<<setw(11)<<s->get_salary_()<<endl;
        total += s->get_salary_();
    }
    ss<<endl;
    ss<<"->  "<<setw(70)<<"total salary:"<<setw(11)<<total<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please press 'q' to return..."<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        if(input == 'q' || input == 'Q' || input == 27) break;
    }
}

void Interaction::SaveData() {
    company_->SaveData("employee.csv");
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Save data"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<"Saved!"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please press 'q' to return..."<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        if(input == 'q' || input == 'Q' || input == 27) break;
    }
}


Company *Interaction::SelectDepartment(string name) {
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* "<<name<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"Select Department:"<<endl<<endl;
    ss<<"->  "<<"(1) Administrative"<<endl<<endl;
    ss<<"->  "<<"(2) Technology"<<endl<<endl;
    ss<<"->  "<<"(3) Market"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        switch(input){
            case '1':
                return this->administrative_;
            case '2':
                return this->technology_;
            case '3':
                return this->market_;
        }
    }
}

void Interaction::AddEmployee() {
    Company *company = SelectDepartment("Add employee");
    map<std::string, int> positions = company->get_position();
    std::string position;
    std::string name;

    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Add employee"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"Select Position:"<<endl<<endl;
    int item = 0;
    for(const auto& s:positions){
        ss<<"->  "<<"("<<++item<<") "<<s.first<<" (level: "<<s.second<<")"<<endl<<endl;
    }
    ss<<endl;
    ss<<"--------------------------------------------------"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        if(input < '1' || input > item+48) continue;
        else{
            map<std::string, int>::iterator it = positions.begin();
            for(int i = 0; i<(input - 49); i++){
                it++;
            }
            position=it->first;
            break;
        }
    }

    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Add employee"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"   Please input employee name:"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin >> name;
    bool ret = company->AddEmployee(new People(name), position);

    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Add employee"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    if(ret){
        ss<<"    "<<"Added successfully!"<<endl<<endl;
    }else{
        ss<<"    "<<"Added failed!"<<endl<<endl;
    }
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please press 'q' to return..."<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    while(true){
        input = getch();
        if(input == 'q' || input == 'Q' || input == 27) break;
    }
}

void Interaction::DeleteEmployee() {
    Company *company = SelectDepartment("Delete employee");
    vector<People*> people = company->ListEmployee();
    string name;
    bool ret;

    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Delete employee"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<setw(8)<<"-index"<<setw(17)<<"-name"<<setw(17)<<"-department"<<
      setw(8)<<"-level"<<setw(20)<<"-position"<<setw(11)<<"-salary"<<endl;
    for(const auto s:people){
        ss<<"->  "<<setw(8)<<s->get_index()<<setw(17)<<s->get_name()<<setw(17)<<s->get_department()
          <<setw(8)<<s->get_level()<<setw(20)<<s->get_position()<<setw(11)<<s->get_salary_()<<endl;
    }
    ss<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please input employee name you want to delete:"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin >> name;

    for(const auto s: company->ListEmployee()){
        if(s->get_name() == name){
            company->RemoveEmplyee(s);
            ret = true;
            break;
        }
        ret = false;
    }

    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Delete employee"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    if(ret){
        ss<<"    "<<"Delete successfully!"<<endl<<endl;
    }else{
        ss<<"    "<<"Delete failed!"<<endl<<endl;
    }
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please press 'q' to return..."<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        if(input == 'q' || input == 'Q' || input == 27) break;
    }
}

void Interaction::SetBonus() {
    string bonus;
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Set bonus"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"   Please input bonus:"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin >>bonus;
    technology_->set_bonus(stof(bonus));


    string line,temp;
    stringstream out;
    ss.clear();
    ss.str("" );

    ifstream ifs("config.csv", ios::in);
    ofstream ofs;

    if(ifs.is_open()){
        bool flag = false;
        while(getline(ifs, line)){
            ss.clear();
            ss.str("");
            ss << line;
            getline(ss ,temp, ',');
            if(temp == technology_->get_co_name()){
                out << temp << ','<<stof(bonus);
                getline(ss ,temp, ',');
                while(getline(ss ,temp, ',')){
                    out<<','<<temp;
                }
                out<<endl;
                flag = true;
            }else{
                out << line <<endl;
            }
        }
        if(!flag){
            out<<technology_->get_co_name()<<','<<stof(bonus)<<endl;
        }
    }else{
        out<<"department,param1"<<endl;
        out<<technology_->get_co_name()<<','<<stof(bonus)<<endl;
    }
    ifs.close();
    ofs.open("config.csv",ios::out);
    ofs<<out.str();
    ofs.close();


    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Set bonus"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<"Complete!"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please press 'q' to return..."<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        if(input == 'q' || input == 'Q' || input == 27) break;
    }
}

void Interaction::SetSales() {
    string sales;
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Set sales"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"   Please input sales:"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin >>sales;
    market_->set_sales(stof(sales));

    stringstream out;
    string line,temp;

    ifstream ifs("config.csv", ios::in);
    ofstream ofs;

    if(ifs.is_open()){
        bool flag = false;
        while(getline(ifs, line)){
            ss.clear();
            ss.str("");
            ss << line;
            getline(ss ,temp, ',');
            if(temp == market_->get_co_name()){
                out << temp <<','<< stof(sales);
                getline(ss ,temp, ',');
                while(getline(ss ,temp, ',')){
                    out<<','<<temp;
                }
                out<<endl;
                flag = true;
            }else{
                out << line <<endl;
            }
        }
        if(!flag){
            out<<market_->get_co_name()<<','<<stof(sales)<<endl;
        }
    }else{
        out<<"department,param1"<<endl;
        out<<market_->get_co_name()<<','<<stof(sales)<<endl;
    }
    ifs.close();
    ofs.open("config.csv",ios::out);
    ofs<<out.str();
    ofs.close();

    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Set sales"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<"Complete!"<<endl<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please press 'q' to return..."<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    char input;
    while(true){
        input = getch();
        if(input == 'q' || input == 'Q' || input == 27) break;
    }
}





