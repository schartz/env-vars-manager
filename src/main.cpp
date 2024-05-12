#include <iostream>
#include <fstream>
#include <map>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/captured_mouse.hpp>
#include <list>
#include <ftxui/dom/table.hpp>
#include "EnvVarsContainerMap.h"
#include "appUtils.h"


int main() {
    /*std::map<std::string, std::string> mainHashMap;
    mainHashMap["hello"] = "world";

    std::cout << mainHashMap["hello"] << "\n";*/

    EnvVarsContainerMap map_container = EnvVarsContainerMap();
    map_container.createEnvMap("dev");

    std::ifstream envFile("env.sample");
    if(!envFile.is_open()) {
        std:: cerr << "Couldn't open env.sample" << std::endl;
        return 1;
    }

    std::string line;
    int line_no = 0;
    while(std::getline(envFile, line)){
        ++line_no;
        line = AppUtils::trim(line);
        if(line.empty() || AppUtils::stringStartsWith(line, "#")){
//           std::cout << "Line no " + << line_no << "is empty" << std::endl;
            continue;
        }
        std::cout << line << std::endl;
        std::vector<std::string> tokens = AppUtils::splitString(line, "=");
        map_container.putEnvVal("dev", tokens[0], tokens[1]);
    }
    envFile.close();
    map_container.save();
    std::cout << map_container.getEnvVal("dev", "TOKEN_SECRET") << std::endl;
    map_container.exportEnvFile("dev");


    std::cout << "EnvVarsContainerMap consumes memory: " << sizeof(map_container)
              << "\n";



    /*
     * FTXUI code
     */
    using namespace ftxui;
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> left_menu_entries = {
            "0%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%",
    };
    std::vector<std::string> right_menu_entries = {
            "0%", "1%", "2%", "3%", "4%", "5%", "6%", "7%", "8%", "9%", "10%",
    };

    auto menu_option = MenuOption();
    menu_option.on_enter = screen.ExitLoopClosure();

    int left_menu_selected = 0;
    int right_menu_selected = 0;
    Component left_menu_ =
            Menu(&left_menu_entries, &left_menu_selected, menu_option);
    Component right_menu_ =
            Menu(&right_menu_entries, &right_menu_selected, menu_option);

    Component container = Container::Horizontal({
                                                        left_menu_,
                                                        right_menu_,
                                                });

    auto renderer = Renderer(container, [&] {
        int sum = left_menu_selected * 10 + right_menu_selected;
        return vbox({
                            // -------- Top panel --------------
                            hbox({
                                         // -------- Left Menu --------------
                                         vbox({
                                                      hcenter(bold(text("Percentage by 10%"))),
                                                      separator(),
                                                      left_menu_->Render(),
                                              }),
                                         separator(),
                                         // -------- Right Menu --------------
                                         vbox({
                                                      hcenter(bold(text("Percentage by 1%"))),
                                                      separator(),
                                                      right_menu_->Render(),
                                              }),
                                         separator(),
                                 }),
                            separator(),
                            // -------- Bottom panel --------------
                            vbox({
                                         hbox({
                                                      text(" gauge : "),
                                                      gauge(sum / 100.0),
                                              }),
                                         hbox({
                                                      text("  text : "),
                                                      text(std::to_string(sum) + " %"),
                                              }),
                                 }),
                    }) |
               border;
    });

    screen.Loop(renderer);
}
