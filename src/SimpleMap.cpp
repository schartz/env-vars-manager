//
// Created by schartz on 02/05/24.
//

#include "SimpleMap.h"
#include <fstream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

void SimpleMap::put(const std::string &key, std::string value) {
    this->simpleMap[key] = std::move(value);
}

bool SimpleMap::contains(const std::string &key) {
    if (this->simpleMap.find(key) != this->simpleMap.end())
        return true;
    return false;
}

std::string SimpleMap::get(const std::string &key) {
    if (this->contains(key)) {
        return this->simpleMap[key];
    }
    std::string error_msg = "key: " + key + " does not exist in the env var map";
    throw std::runtime_error(error_msg);
}

unsigned long SimpleMap::len() {
    unsigned long count = this->simpleMap.size();
    return count;
}

std::vector<std::string> SimpleMap::listKeys() {
    std::vector<std::string> keysList, valueList;
    for (std::map<std::string, std::string>::iterator iter =
            this->simpleMap.begin();
         iter != this->simpleMap.end(); ++iter) {
        keysList.push_back(iter->first);
        valueList.push_back(iter->second);
    }

    return keysList;
}


void SimpleMap::exportToFile(const std::string &filename) {
    std::ofstream outfile;
    outfile.open(filename);
    if(!outfile.is_open()){
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return;
    }
    std::cout << "opened file " + filename << std::endl;

    for (std::map<std::string, std::string>::iterator iter =
            this->simpleMap.begin();
         iter != this->simpleMap.end(); ++iter) {
        outfile <<
        iter->first <<
        "=" <<
        "'" <<
        iter->second <<
        "'" <<
        std::endl;
    }
    outfile.close();


}
