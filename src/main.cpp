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

    //auto map_container = EnvVarsContainerMap::load("envVars.bin");

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
            continue;
        }
        std::cout << line << std::endl;
        std::vector<std::string> tokens = AppUtils::splitString(line, "=");
        map_container.putEnvVal("dev", tokens[0], tokens[1]);
        map_container.putEnvVal("staging", tokens[0], tokens[1]);
        map_container.putEnvVal("production", tokens[0], tokens[1]);
    }
    envFile.close();
    map_container.save();
//    std::cout << "loaded!!!!" << std::endl;
    auto k = map_container.listEnvs();
    std::for_each(k.begin(), k.end(), [&](const auto &item) {
        std::cout << item << std::endl;
    });
//    std::cout<<  << std::endl;
//    std::cout << map_container.listEnvs() << std::endl;
    std::cout << map_container.getEnvVal("dev", "TOKEN_SECRET") << std::endl;
    map_container.exportEnvFile("dev");

    std::cout << "EnvVarsContainerMap consumes memory: " << sizeof(map_container) << "\n";
    auto availableEnvs = map_container.listEnvs();



    /*
     * FTXUI code
     */
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    std::vector<std::string> left_menu_entries = {
            "0%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%",
    };
    left_menu_entries = availableEnvs;
    std::vector<std::string> right_menu_entries = {
            "Create an empty env", "Clone this env", "Export this env to file", "Edit/view this env"
    };

    auto table = Table({
                               {"Version", "Marketing name", "Release date", "API level", "Runtime"},
                               {"2.3", "Gingerbread", "February 9 2011", "10", "Dalvik 1.4.0"},
                               {"4.0", "Ice Cream Sandwich", "October 19 2011", "15", "Dalvik"},
                               {"4.1", "Jelly Bean", "July 9 2012", "16", "Dalvik"},
                               {"4.2", "Jelly Bean", "November 13 2012", "17", "Dalvik"},
                               {"4.3", "Jelly Bean", "July 24 2013", "18", "Dalvik"},
                               {"4.4", "KitKat", "October 31 2013", "19", "Dalvik and ART"},
                               {"5.0", "Lollipop", "November 3 2014", "21", "ART"},
                               {"5.1", "Lollipop", "March 9 2015", "22", "ART"},
                               {"6.0", "Marshmallow", "October 5 2015", "23", "ART"},
                               {"7.0", "Nougat", "August 22 2016", "24", "ART"},
                               {"7.1", "Nougat", "October 4 2016", "25", "ART"},
                               {"8.0", "Oreo", "August 21 2017", "26", "ART"},
                               {"8.1", "Oreo", "December 5 2017", "27", "ART"},
                               {"9", "Pie", "August 6 2018", "28", "ART"},
                               {"10", "10", "September 3 2019", "29", "ART"},
                               {"11", "11", "September 8 2020", "30", "ART"},
                       });

    table.SelectAll().Border(LIGHT);

    // Add border around the first column.
    table.SelectColumn(0).Border(LIGHT);

    // Make first row bold with a double border.
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);

    // Align right the "Release date" column.
    table.SelectColumn(2).DecorateCells(align_right);

    // Select row from the second to the last.
    auto content = table.SelectRows(1, -1);
    // Alternate in between 3 colors.
    content.DecorateCellsAlternateRow(color(Color::Blue), 3, 0);
    content.DecorateCellsAlternateRow(color(Color::Cyan), 3, 1);
    content.DecorateCellsAlternateRow(color(Color::White), 3, 2);

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
                                                      hcenter(bold(text("Available envs"))),
                                                      separator(),
                                                      left_menu_->Render(),
                                              }),
                                         separator(),
                                         // -------- Right Menu --------------
                                         vbox({
                                                      hcenter(bold(text("Available Commands"))),
                                                      separator(),
                                                      right_menu_->Render(),
                                              }),
                                         separator(),
                                         vbox({
                                                      hcenter(bold(text("Data"))),
                                                      separator(),
                                                      table.Render(),
                                              }),
                                         separator(),
                                 }),
                            separator(),
                            // -------- Bottom panel --------------
                            vbox({
                                         hbox({
                                                      text(" Selected env : "),
                                                      text(availableEnvs[left_menu_selected]) | color(Color::White) | bgcolor(Color::Blue),
                                              }),
                                         hbox({
                                                      text("  Keys in env : "),
                                                      text(std::to_string(map_container.getEnvMapByEnvName(availableEnvs[left_menu_selected]).len())),
                                              }),
                                 }),
                    }) |
               border;
    });

    screen.Loop(renderer);
}
