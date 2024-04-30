#include <map>
#include <string>
#include <vector>

class SimpleMap {
  std::map<std::string, std::string> simpleMap;

public:
  void put(const std::string key, const std::string value);
  std::string get(const std::string key);
  unsigned long len();
  bool contains(std::string key);
  std::vector<std::string> listKeys();
  void exportToFile();
};

class EnvVarsContainerMap {
  std::map<std::string, SimpleMap> envMapContainer;

public:
  void putEnvVal(const std::string environment_name, const std::string key,
                 const std::string value);

  SimpleMap getEnvMapByEnvName(const std::string environment_name);
  std::string getEnvVal(const std::string environment_name,
                        const std::string key);

  int len();
  int lenByEnvName(const std::string environment_name);
  bool containsKey(const std::string environment_name, std::string key);
  bool containsEnvMap(const std::string environment_name);
  std::vector<std::string> listEnvs();

  void exportEnvFile(std::string environment_name);
};
