#include "ExternCommands.h"

#include <iostream>

#define READ_END  0
#define WRITE_END 1

ExternCommands::ExternCommands(std::vector<Command> commands) {
  std::string data = "";
  for (auto command : commands) {
    for (auto item : command) {
      if (item == "|" || item == ";" || item == "&") {
        if (data.length() > 0) {
          this->commands_.push_back(data);
          data = "";
        }
        this->commands_.push_back({item});
      } else {
        if (data.length() > 0) {
          data += " ";
        }
        data += item;
      }
    }
  }
  if (data.length() > 0) {
    this->commands_.push_back(data);
  }
  this->pipe_size_ = this->commands_.size() / 2;
  std::cout << this->pipe_size_ << std::endl;
}

command_result ExternCommands::execute() {
  return command_result(0, 0);
} 