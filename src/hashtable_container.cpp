#include "hashtable_container.h"

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

/**
 *
 * SimpleMap class definitions begin.
 *
 **/

void SimpleMap::put(std::string key, std::string value) {
  this->simpleMap[key] = value;
}

bool SimpleMap::contains(std::string key) {
  if (this->simpleMap.find(key) != this->simpleMap.end())
    return true;
  return false;
}

std::string SimpleMap::get(const std::string key) {
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

/**
 *
 * EnvVarsContainerMap class definitaions begin
 *
 **/

void EnvVarsContainerMap::putEnvVal(const std::string environment_name,
                                    const std::string key,
                                    const std::string value) {
  this->envMapContainer[environment_name].put(key, value);
}

SimpleMap
EnvVarsContainerMap::getEnvMapByEnvName(const std::string environment_name) {
  if (this->containsEnvMap(environment_name)) {
    return this->envMapContainer[environment_name];
  }

  std::string error_msg = "environment map: " + environment_name +
                          " does not exist in the env var container";
  throw std::runtime_error(error_msg);
}
std::string EnvVarsContainerMap::getEnvVal(const std::string environment_name,
                                           const std::string key) {
  if (this->containsEnvMap(environment_name)) {
    return this->envMapContainer[environment_name].get(key);
  }
  std::string error_msg = "environment map: " + environment_name +
                          " does not exist in the env var container";
  throw std::runtime_error(error_msg);
}

bool EnvVarsContainerMap::containsEnvMap(const std::string environment_name) {
  if (this->envMapContainer.find(environment_name) !=
      this->envMapContainer.end())
    return true;
  return false;
}

bool EnvVarsContainerMap::containsKey(const std::string environment_name,
                                      std::string key) {
  if (this->containsEnvMap(environment_name)) {
    if (this->envMapContainer[environment_name].contains(key)) {
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
int EnvVarsContainerMap::len() {
  unsigned long count = this->envMapContainer.size();
  return count;
}
int EnvVarsContainerMap::lenByEnvName(const std::string environment_name) {
  if (this->containsEnvMap(environment_name)) {
    return this->envMapContainer[environment_name].len();
  }

  std::string error_msg = "environment map: " + environment_name +
                          " does not exist in the env var container";
  throw std::runtime_error(error_msg);
}
