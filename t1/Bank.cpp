//
// Created by jungh on 16/11/2020.
//

#include <fstream>

#include "Bank.h"

using namespace std;



Bank::Bank(std::string currency):currency_(currency){
    ifstream file("..\\rate.txt");
    if(!file.is_open()){
        std::cerr << "open param file failed." << std::endl;
        exit(-1);
    }

    string line;
    while(getline(file, line)){
        vector<string> sline;
        SplitString(line, sline, ':');
        if(sline[0] == currency_) {
            exchange_rate_ = atof(sline[1].c_str());
            return;
        }
    }
    std::cerr << "no parameter." << std::endl;
    exit(-1);
};

double Bank::RMB2FC(double money) const {
    return money * 100 / exchange_rate_;
}

double Bank::FC2RMB(double money) const {
    return money * exchange_rate_ / 100;
}

void Bank::SplitString(const string& s, vector<string>& tokens, char delim) {
    tokens.clear();
    auto string_find_first_not = [s, delim](size_t pos = 0) -> size_t {
        for (size_t i = pos; i < s.size(); i++) {
            if (s[i] != delim) return i;
        }
        return string::npos;
    };
    size_t lastPos = string_find_first_not(0);
    size_t pos = s.find(delim, lastPos);
    while (lastPos != string::npos) {
        tokens.emplace_back(s.substr(lastPos, pos - lastPos));
        lastPos = string_find_first_not(pos);
        pos = s.find(delim, lastPos);
    }
}

Bank* Factory::GetBank(FACTORY_CURRENCY index){
    switch(index){
        case FACTORY_CURRENCY_POUND:
            return new Pound();
            break;
        case FACTORY_CURRENCY_EURO:
            return new Euro();
            break;
        default:
            return nullptr;
    }
}
