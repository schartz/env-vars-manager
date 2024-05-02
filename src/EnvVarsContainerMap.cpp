//
// Created by schartz on 02/05/24.
//

#include "EnvVarsContainerMap.h"
#include "SimpleMap.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

void EnvVarsContainerMap::putEnvVal(const std::string& environment_name,
                                    const std::string& key,
                                    const std::string& value) {
    this->envMapContainer[environment_name].put(key, value);
}



void EnvVarsContainerMap::createEnvMap(const std::string& environment_name){
    this->envMapContainer[environment_name] = SimpleMap();
}


SimpleMap
EnvVarsContainerMap::getEnvMapByEnvName(const std::string& environment_name) {
    if (this->containsEnvMap(environment_name)) {
        return this->envMapContainer[environment_name];
    }

    std::string error_msg = "environment map: " + environment_name +
                            " does not exist in the env var container";
    throw std::runtime_error(error_msg);
}
std::string EnvVarsContainerMap::getEnvVal(const std::string& environment_name,
                                           const std::string& key) {
    if (this->containsEnvMap(environment_name)) {
        return this->envMapContainer[environment_name].get(key);
    }
    std::string error_msg = "environment map: " + environment_name +
                            " does not exist in the env var container";
    throw std::runtime_error(error_msg);
}

bool EnvVarsContainerMap::containsEnvMap(const std::string& environment_name) {
    if (this->envMapContainer.find(environment_name) !=
        this->envMapContainer.end())
        return true;
    return false;
}

bool EnvVarsContainerMap::containsKey(const std::string& environment_name,
                                      std::string key) {
    if (this->containsEnvMap(environment_name)) {
        if (this->envMapContainer[environment_name].contains(std::move(key))) {
            return true;
        }
    }
    return false;
}
std::vector<std::string> EnvVarsContainerMap::listEnvs() {
    std::vector<std::string> keysList;
    for (std::map<std::string, SimpleMap>::iterator iter =
            this->envMapContainer.begin();
         iter != this->envMapContainer.end(); ++iter) {
        keysList.push_back(iter->first);
    }

    return keysList;
}
unsigned long EnvVarsContainerMap::len() {
    unsigned long count = this->envMapContainer.size();
    return count;
}
unsigned long EnvVarsContainerMap::lenByEnvName(const std::string& environment_name) {
    if (this->containsEnvMap(environment_name)) {
        return this->envMapContainer[environment_name].len();
    }

    std::string error_msg = "environment map: " + environment_name +
                            " does not exist in the env var container";
    throw std::runtime_error(error_msg);
}

void EnvVarsContainerMap::save(){
    std::ofstream saveFile("envVars.bin", std::ios::binary);
    if(!saveFile.is_open()){
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return;
    }
    saveFile.write(reinterpret_cast<const char*>(this), sizeof(*this));
    saveFile.close();
    std::cout << "state saved." << std::endl;
}

EnvVarsContainerMap EnvVarsContainerMap::load(const std::string& saveFileName){
    EnvVarsContainerMap loadedObject;
    std::ifstream file(saveFileName, std::ios::binary);
    if(!file.is_open()){
        std::cerr << "Error: Failed to open file for reading." << std::endl;
        return loadedObject;
    }

    file.read(reinterpret_cast<char*>(&loadedObject), sizeof(loadedObject));
    file.close();
    std::cout << "state loaded." << std::endl;
    return loadedObject;


}

void EnvVarsContainerMap::exportEnvFile(const std::string& environment_name) {
    if (this->containsEnvMap(environment_name)) {
        this->envMapContainer[environment_name].exportToFile(environment_name + "-file.env");
        return;
    }
    std::string error_msg = "environment map: " + environment_name +
                            " does not exist in the env var container";
    throw std::runtime_error(error_msg);
}
