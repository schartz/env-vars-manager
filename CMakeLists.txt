cmake_minimum_required(VERSION 3.26)
project(envVarMgr)



############ Fetch FTXUI ####################
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v4.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

###########################################



set(CMAKE_CXX_STANDARD 17)

add_executable(envVarMgr src/main.cpp
        src/EnvVarsContainerMap.cpp
        src/EnvVarsContainerMap.h
        src/SimpleMap.cpp
        src/SimpleMap.h
        src/appUtils.cpp
        src/appUtils.h
        src/base64.hpp)

############ Setup dependencies/libraries ####################

# Setup FTXUI ------------------------------------------------
target_link_libraries(envVarMgr
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
)