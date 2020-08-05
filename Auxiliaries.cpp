//
// Created by avira on 04/08/2020.
//

#include "GraphCalc.h"
#include "Auxiliaries.h"

bool startsWith(const std::string& line, const std::string& starter) {
    return line.find(starter) == START_OF_LINE;
}

bool endsWith(const std::string& line, const std::string& ender) {
    //  TODO test if this true
    return line.rfind(ender) == line.length() - ender.length();
}

std::string rtrim(std::string &str) {
    if(str.empty()) {
        return str;
    }
    std::string rtrimmed_str(str);
   for(int i = str.length() - 1 ; i != -1 ; i--) {
       if(isspace(str[i])) {
           rtrimmed_str.pop_back();
       }
       else {
           break;
       }
   }
    return rtrimmed_str;

}

std::string ltrim(std::string &str) {
    if(str.empty()) {
        return str;
    }
    std::string ltrimmed_str(str);
    for(char c : str) {
        if(isspace(c)) {
            ltrimmed_str.erase(0,1);
        }
        else {
            break;
        }
    }
    return ltrimmed_str;

}

std::string trim(std::string &str) {
    std::string rtrimmed = rtrim(str);
    return ltrim(rtrimmed);
}