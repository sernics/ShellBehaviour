#include "InterCommnads.h"
#include <unistd.h>

InterCommands::InterCommands(std::vector<Command> args) : args_(args) {}

command_result InterCommands::execute() {
  if (args_[0][0] == "cd") {
    return this->cd_command().return_value;
  }
}

command_result InterCommands::cd_command() { 
  int exit_code = chdir(args_[0][1].c_str()); 
  return command_result(exit_code, 0);
}