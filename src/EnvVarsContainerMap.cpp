//
// Created by schartz on 02/05/24.
//

#include "EnvVarsContainerMap.h"
#include "SimpleMap.h"
#include "appUtils.h"
#include "base64.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <iterator>

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
    // define separators
    const std::string env_to_env_separator = "\n----->";
    const std::string key_to_value_separator = "=====";
    const std::string key_value_to_next_separator = "|||||";
    const std::string env_name_to_env_val_separator = "^^^^^";


    std::vector<std::string> envStrings;
    auto envs = this->listEnvs();

    for (const auto &envName: envs){
        auto env = this->getEnvMapByEnvName(envName);
        std::string envStr = "";
        envStr += envName;
        envStr.append(env_name_to_env_val_separator);

        auto envKeys = this->envMapContainer[envName].listKeys();
        for (const auto &key: envKeys){
            auto val = this->getEnvVal(envName, key);
            if (val.empty()) val = "''";
            envStr.append(key_value_to_next_separator).append(key).append(key_to_value_separator).append(val);
        }
        envStrings.push_back(envStr);
    }
    const auto final_data_string = AppUtils::join(envStrings, env_to_env_separator);
    const auto encoded = base64::to_base64(final_data_string);


    std::ofstream saveFile("envVars.bin");
    if(!saveFile.is_open()){
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return;
    }
    saveFile << encoded;
    saveFile.close();


    std::ofstream outFile("output.txt");
    if(!outFile.is_open()){
        std::cerr << "Error: Failed to open file output.txt for writing." << std::endl;
        return;
    }
    outFile << final_data_string;
    outFile.close();
    std::cout << "output..txt saved." << std::endl;

    std::cout << "state saved." << std::endl;
}

EnvVarsContainerMap EnvVarsContainerMap::load(const std::string& saveFileName){
    std::ifstream binary_file(saveFileName);
    auto my_str = std::string();
    binary_file >> my_str;
    auto decoded = base64::from_base64(my_str);

    std::ofstream outFile("output_from_binary.txt");
    if(!outFile.is_open()){
        std::cerr << "Error: Failed to open file output.txt for writing." << std::endl;
    }
    outFile << decoded;
    outFile.close();
    std::cout << "output_from_binary..txt saved." << std::endl;



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
