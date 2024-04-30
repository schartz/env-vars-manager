cmake_minimum_required (VERSION 3.11)
 
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)
 
project(env-vars-manager.app LANGUAGES CXX VERSION 1.0.0)
add_executable(env-vars-manager.app src/main.cpp)
target_link_libraries(env-vars-manager.app
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)
