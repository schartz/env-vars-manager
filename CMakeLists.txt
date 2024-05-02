cmake_minimum_required(VERSION 3.26)
project(envVarMgr)

set(CMAKE_CXX_STANDARD 17)

add_executable(envVarMgr src/main.cpp
        src/EnvVarsContainerMap.cpp
        src/EnvVarsContainerMap.h
        src/SimpleMap.cpp
        src/SimpleMap.h)
