#include "ExternCommands.h"

#include <iostream>

ExternCommands::ExternCommands(std::vector<Command> commands) {
  std::string data = "";
  for (auto command : commands) {
    for (auto item : command) {
      if (item != "|" || item != ";" || item != "&") {
        data += item;
        data += " ";
      } else {
        commands_.push_back(data);
        data = "";
        commands_.push_back({item});
      }
    }
  }
  commands_.push_back(data);
  for (const auto command : this->commands_) {
    std::cout << command << std::endl;
  }
}

command_result ExternCommands::execute() {
  return command_result(0, 0);
}