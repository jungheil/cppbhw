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
        ss<<"->  "<<"(4) Change position."<<endl<<endl;
        ss<<"->  "<<"(5) Set bonus."<<endl<<endl;
        ss<<"->  "<<"(6) Set sales."<<endl<<endl;
        ss<<"->  "<<"(7) Save data."<<endl<<endl;
        ss<<"->  "<<"(8) Exit."<<endl<<endl;
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
                ChangePosition();
                break;
            case '5':
                SetBonus();
                break;
            case '6':
                SetSales();
                break;
            case '7':
                SaveData();
                break;
            case '8':
                if(RUSure("EXIT")) run = false;
                break;
            case 27:
                if(RUSure("EXIT")) run = false;
                break;
        }
    }
}

void Interaction::List() {
    long double total = 0;
    vector<People*> people = company_->ListEmployee();
    sort(people.begin(),people.end(),CompareSalary);
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* List all employees(Salary ascending)"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<setw(8)<<"-index"<<setw(17)<<"-name"<<setw(17)<<"-department"<<
            setw(8)<<"-level"<<setw(20)<<"-position"<<setw(11)<<"-salary"<<endl;
    for(const auto s:people){
        ss<<"->  "<<setw(8)<<s->get_index()<<setw(17)<<s->get_name()<<setw(17)<<s->get_department()->get_co_name()
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
    if(!RUSure("Save data")) return;

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

bool Interaction::RUSure(std::string name) {
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* "<<name<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;

    ss<<"    "<<"Are you sure to do this? [y/N]"<<endl<<endl;

    ss<<"--------------------------------------------------"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin.sync();
//    cin.clear();
    char sure = cin.get();
    cin.sync();
    if(sure != 'Y' && sure != 'y' ) return false;
    else return true;
}

void Interaction::FalseReturn(std::string name, std::string type) {
    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* "<<name<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;

    ss<<"    "<<"Change failed! ("<<type<<")"<<endl<<endl;

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
        if(input == 'q' || input == 'Q' || input == 27) return;
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
            auto it = positions.begin();
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

    if(!RUSure("Add employee")) return;


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
//    Company *company = SelectDepartment("Delete employee");
    vector<People*> people = company_->ListEmployee();
    int index;
    bool ret;

    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Delete employee"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<setw(8)<<"-index"<<setw(17)<<"-name"<<setw(17)<<"-department"<<
      setw(8)<<"-level"<<setw(20)<<"-position"<<setw(11)<<"-salary"<<endl;
    for(const auto s:people){
        ss<<"->  "<<setw(8)<<s->get_index()<<setw(17)<<s->get_name()<<setw(17)<<s->get_department()->get_co_name()
          <<setw(8)<<s->get_level()<<setw(20)<<s->get_position()<<setw(11)<<s->get_salary_()<<endl;
    }
    ss<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please input employee index you want to delete:"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin >> index;

    if(!RUSure("Delete employee")) return;


    for(const auto s: company_->ListEmployee()){
        if(s->get_index() == index){
            s->get_department()->RemoveEmplyee(s);
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

void Interaction::ChangePosition() {
//    Company *company = SelectDepartment("Delete employee");
    vector<People*> people = company_->ListEmployee();
    int index;
    bool ret;
    People* target;

    stringstream ss;
    ss<<"=================================================="<<endl;
    ss<<"* Change position"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"    "<<setw(8)<<"-index"<<setw(17)<<"-name"<<setw(17)<<"-department"<<
      setw(8)<<"-level"<<setw(20)<<"-position"<<setw(11)<<"-salary"<<endl;
    for(const auto s:people){
        ss<<"->  "<<setw(8)<<s->get_index()<<setw(17)<<s->get_name()<<setw(17)<<s->get_department()->get_co_name()
          <<setw(8)<<s->get_level()<<setw(20)<<s->get_position()<<setw(11)<<s->get_salary_()<<endl;
    }
    ss<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please input employee index you want to Change:"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    cin >> index;

    for(const auto s: company_->ListEmployee()){
        if(s->get_index() == index){
            target = s;
            ret = true;
            break;
        }
        ret = false;
    }

    if(!ret){
        FalseReturn("Change position","No such person");
        return;
    }

    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Change position"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    ss<<"Select Position:"<<endl<<endl;
    int item = 0;
    for(const auto& s:target->get_department()->get_position()){
        ss<<"->  "<<"("<<++item<<") "<<s.first<<" (level: "<<s.second<<")"<<endl<<endl;
    }
    ss<<endl;
    ss<<"--------------------------------------------------"<<endl;
    ss<<"Please input the position index you want to change:"<<endl;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED|
                            BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
    cout<<"# "<<"STAFF MANAGEMENT SYSTEM"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    cout<<ss.str();

    int ps_id;
    cin >> ps_id;
    if(!RUSure("Change position")) return;

    if(ps_id > target->get_department()->get_position().size() || ps_id < 1){
        FalseReturn("Change position", "No such position");
        return;
    }
    auto it = target->get_department()->get_position().begin();
    for(;ps_id > 1;ps_id--) it++;
    ret = target->get_department()->ChangePosition(target,it->first);

    ss.clear();
    ss.str("");
    ss<<"=================================================="<<endl;
    ss<<"* Change position"<<endl;
    ss<<"--------------------------------------------------"<<endl<<endl;
    if(ret){
        ss<<"    "<<"Change successfully!"<<endl<<endl;
    }else{
        ss<<"    "<<"Change failed!"<<endl<<endl;
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

    if(!RUSure("Set bonus")) return;

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

    if(!RUSure("Set sales")) return;

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





