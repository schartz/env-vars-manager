#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <map>

#include "hashtable_container.h"

int main(void) {

  using namespace ftxui;

  std::map<std::string, std::string> mainHashMap;
  mainHashMap["hello"] = "world";

  std::cout << mainHashMap["hello"] << "\n";

  EnvVarsContainerMap container = EnvVarsContainerMap();

  std::cout << "EnvVarsContainerMap consumes memory: " << sizeof(container)
            << "\n";

  // Define the document
  Element document = hbox({
      text("left") | border,
      text("middle") | border | flex,
      text("right") | border,
  });

  auto screen = Screen::Create(Dimension::Full(),       // Width
                               Dimension::Fit(document) // Height
  );
  Render(screen, document);
  screen.Print();

  return EXIT_SUCCESS;
}
