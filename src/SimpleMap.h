//
// Created by schartz on 02/05/24.
//

#ifndef ENVVARMGR_SIMPLEMAP_H
#define ENVVARMGR_SIMPLEMAP_H
#include <map>
#include <string>
#include <vector>


class SimpleMap {
    std::map<std::string, std::string> simpleMap;

public:
    void put(const std::string& key, std::string value);
    std::string get(const std::string& key);
    unsigned long len();
    bool contains(const std::string& key);
    std::vector<std::string> listKeys();
    void exportToFile(const std::string& filename);
};


#endif //ENVVARMGR_SIMPLEMAP_H
