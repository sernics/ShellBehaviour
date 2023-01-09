#include "ExternCommands.h"

ExternCommands::ExternCommands(std::vector<Command> commands) {
  std::string data = "";
  for (auto command : commands) {
    for (auto item : command) {
      if (item != "|" || item != ";" || item != "&") {
        data += item;
      } else {
        commands_.push_back(data);
        data = "";
        commands_.push_back({item});
      }
    }
  }
  for (const auto command : this->commands_) {
    std::cout << command << std::endl;
  }
}