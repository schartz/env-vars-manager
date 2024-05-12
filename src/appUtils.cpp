//
// Created by schartz on 12/05/24.
//

#include <vector>
#include <string>
#include "appUtils.h"


std::vector<std::string> AppUtils::splitString(std::string input_string, std::string delimiter){
    std::vector<std::string> substrs;
    size_t position = 0;
    std::string token;
    while((position = input_string.find(delimiter)) != std::string::npos) {
        token = input_string.substr(0, position);
        substrs.push_back(token);
        input_string.erase(0, position + delimiter.size());
    }
    substrs.push_back(input_string);
    return substrs;
}



bool AppUtils::stringStartsWith(const std::string& str, const std::string& prefix) {
    return str.substr(0, prefix.size()) == prefix;
}

// trim from left
std::string& AppUtils::ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
std::string& AppUtils::rtrim(std::string& s, const char* t)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
std::string& AppUtils::trim(std::string& s, const char* t)
{
    return ltrim(rtrim(s, t), t);
}

// copying versions

std::string AppUtils::ltrim_copy(std::string s, const char* t)
{
    return ltrim(s, t);
}

std::string AppUtils::rtrim_copy(std::string s, const char* t)
{
    return rtrim(s, t);
}

std::string AppUtils::trim_copy(std::string s, const char* t)
{
    return trim(s, t);
}
