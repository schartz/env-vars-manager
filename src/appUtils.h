//
// Created by schartz on 12/05/24.
//

#ifndef ENVVARMGR_APPUTILS_H
#define ENVVARMGR_APPUTILS_H


//
// Created by schartz on 12/05/24.
//

#include <vector>
#include <string>

class AppUtils{
public:
    static std::vector<std::string> splitString(std::string input_string, const std::string& delimiter);

    static bool stringStartsWith(const std::string& str, const std::string& prefix);

    static bool stringEndsWith(const std::string& str, const std::string& suffix);

    static std::string join(const std::vector<std::string>& stringVector, const std::string& delimiter);

// trim from left
    static std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");

// trim from right
    static std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");

// trim from left & right
    static std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");

// copying versions

    static std::string ltrim_copy(std::string s, const char* t = " \t\n\r\f\v");

    static std::string rtrim_copy(std::string s, const char* t = " \t\n\r\f\v");

    static std::string trim_copy(std::string s, const char* t = " \t\n\r\f\v");

};





#endif //ENVVARMGR_APPUTILS_H
