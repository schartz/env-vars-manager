//
// Created by schartz on 02/05/24.
//

#ifndef ENVVARMGR_ENVVARSCONTAINERMAP_H
#define ENVVARMGR_ENVVARSCONTAINERMAP_H

#include "SimpleMap.h"
#include <map>
#include <string>
#include <vector>

class EnvVarsContainerMap {
    std::map<std::string, SimpleMap> envMapContainer;

public:
    void putEnvVal(const std::string& environment_name, const std::string& key,
                   const std::string& value);
    void createEnvMap(const std::string& environment_name);
    SimpleMap getEnvMapByEnvName(const std::string& environment_name);
    std::string getEnvVal(const std::string& environment_name,
                          const std::string& key);

    unsigned long len();
    unsigned long lenByEnvName(const std::string& environment_name);
    bool containsKey(const std::string& environment_name, std::string key);
    bool containsEnvMap(const std::string& environment_name);
    std::vector<std::string> listEnvs();

    void exportEnvFile(const std::string& environment_name);
    void save();
    static EnvVarsContainerMap load(const std::string& saveFileName);
};


#endif //ENVVARMGR_ENVVARSCONTAINERMAP_H
