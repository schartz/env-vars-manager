#include <iostream>
#include <map>
#include "EnvVarsContainerMap.h"

int main() {
    std::map<std::string, std::string> mainHashMap;
    mainHashMap["hello"] = "world";

    std::cout << mainHashMap["hello"] << "\n";

    EnvVarsContainerMap container = EnvVarsContainerMap();

    container.createEnvMap("dev");
    container.putEnvVal("dev", "APP_URL", "https://allps.ai");
    container.save();
    std::cout << container.getEnvVal("dev", "APP_URL") << std::endl;
    container.exportEnvFile("dev");





    std::cout << "EnvVarsContainerMap consumes memory: " << sizeof(container)
              << "\n";


    return 0;
}
