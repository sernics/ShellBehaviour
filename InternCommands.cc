#include "InterCommnads.h"
#include <unistd.h>
#include <iostream>

InterCommands::InterCommands(std::vector<Command> args) : args_(args) {}

command_result InterCommands::execute() {
  if (args_[0][0] == "cd") {
    return this->cd_command().return_value;
  } if (args_[0][0] == "echo") {
    return this->echo_command().return_value;
  }
}

command_result InterCommands::cd_command() { 
  int exit_code = chdir(args_[0][1].c_str()); 
  return command_result(exit_code, 0);
}

command_result InterCommands::echo_command() {
  std::string result = "";
  for (int i{1}; i < this->args_[0].size(); i++) {
    result += this->args_[0][i];
    result += " ";
  } 
  std::cout << result << std::endl;
  return command_result(0, 0);
}

command_result InterCommands::cp_command() {
  // TODO
}

command_result InterCommands::mv_command() {
  // TODO
}