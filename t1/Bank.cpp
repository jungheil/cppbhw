//
// Created by jungh on 16/11/2020.
//

#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>


#include "Bank.h"

using namespace std;


double Currency::RMB2FC(double money) const {
    return money * 100 / exchange_rate_;
}

double Currency::FC2RMB(double money) const {
    return money * exchange_rate_ / 100;
}

Bank::Bank(string path) {
    stringstream ss;
    string name;
    string rate;
    ifstream fs(path);
    if(!fs.is_open()){
        perror("Bank");
        cout<<"Please input any key to continues..."<<endl;
        getch();
        exit(1);
    }
    getline(fs, name);
    while(getline(fs, name)){
        ss.clear();
        ss.str("");
        ss<<name;
        getline(ss ,name, ',');
        getline(ss,rate,',');
        currency_.push_back(Currency(name,stof(rate)));
    }
    size_=currency_.size();
}

const Currency *Bank::Get(string name) {
    for(const auto& s:currency_){
        if(s.get_name() == name) return &s;
    }
    return nullptr;
}

const Currency *Bank::Get(int index) {
    if(currency_.size()>index){
        vector<Currency>::iterator it = currency_.begin()+index;
        return (Currency*)&(*it);
    }
    return nullptr;
}

void UI::Run() {
    char input;
    bool run = true;
    while(run){
        stringstream ss;
        ss<<"=================================================="<<endl;
        ss << ">>  " << "path: / " << endl;
        ss << "--------------------------------------------------" << endl<< endl;
        ss<<"OPTIONS:"<<endl<<endl;
        ss<<"->  "<<"(1) Foreign currency to RMB."<<endl<<endl;
        ss<<"->  "<<"(2) RMB to foreign currency."<<endl<<endl;
        ss<<"->  "<<"(3) EXIT SYSTEM."<<endl<<endl;
        ss<<"--------------------------------------------------"<<endl;

        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED|
                                BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
        cout<<"# "<<"EXCHANGE OFFICE"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
        cout<<ss.str();

        input = getch();
        switch(input){
            case '1':
                exchange_type_ = EXCHANGE_TYPE_FC2RMB;
                ChoiceCurrency("/ FC2RMB");
                break;
            case '2':
                exchange_type_ = EXCHANGE_TYPE_RMB2FC;
                ChoiceCurrency("/ RMB2FC");
                break;
            case '3':
                run = false;
        }
    }
}

void UI::ChoiceCurrency(string spath) {
    do{
        stringstream ss;
        ss << "==================================================" << endl;
        ss << ">>  " << "path: " << spath << endl;
        ss << "--------------------------------------------------" << endl<< endl;
        ss << "CURRENCY:" << endl << endl;
        int i = 1;
        for (const auto &s : bank_->get_all()) {
            ss << "->  " << "(" << i++ << ") " << s.get_name() << endl << endl;
        }
        ss << "--------------------------------------------------" << endl;
        ss << "Input index (NEED ENTER): " << endl;
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED |
                                BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << "# " << "EXCHANGE OFFICE" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << ss.str();

        string input;
        cin>>input;
        currency_ = bank_->Get(stoi(input)-1);
    }while(currency_ == nullptr);
    Exchange(spath+" / "+currency_->get_name());
}

void UI::Exchange(string spath) {
    bool flag = true;


    while(flag){
        stringstream ss;
        ss << "==================================================" << endl;
        ss << ">>  " << "path: " << spath << endl;
        ss << "--------------------------------------------------" << endl<<endl;
        ss << "EXCHANGE:" << endl << endl;
        if(exchange_type_ == EXCHANGE_TYPE_FC2RMB){
            ss << "\t***\t" << currency_->get_name()<<"\t==>\t***\tRMB"<<endl<<endl;
        }else{
            ss << "\t***\tRMB\t=>\t***\t" << currency_->get_name()<<endl<<endl;
        }
        ss << "--------------------------------------------------" << endl;
        ss << "INPUT THE AMOUNT:" << endl;

        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED |
                                BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << "# " << "EXCHANGE OFFICE" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << ss.str();

        string amount;
        cin >> amount;

        ss.clear();
        ss.str("");
        ss << "==================================================" << endl;
        ss << ">>  " << "path: " << spath << endl;
        ss << "--------------------------------------------------" << endl<<endl;
        ss << "EXCHANGE:" << endl << endl;
        if(exchange_type_ == EXCHANGE_TYPE_FC2RMB){
            ss <<"\t"<< stof(amount) <<"\t" << currency_->get_name()<<"\t=>\t"<<currency_->FC2RMB(stof(amount))<<"\tRMB"<<endl<<endl;
        }else{
            ss <<"\t"<< stof(amount) <<"\tRMB\t==>\t" <<currency_->RMB2FC(stof(amount))<<"\t" <<currency_->get_name()<<endl<<endl;
        }
        ss << "--------------------------------------------------" << endl<<endl;
        ss<<"->  "<<"(1) Continue."<<endl<<endl;
        ss<<"->  "<<"(2) Return."<<endl<<endl;
        ss<<"--------------------------------------------------"<<endl;

        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED |
                                BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        cout << "# " << "EXCHANGE OFFICE" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << ss.str();

        char input;
        while(true){
            input = getch();
            if(input == '1'){
                break;
            }else if(input == '2'){
                flag = false;
                break;
            }
        }
    }

}