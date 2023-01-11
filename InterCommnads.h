#ifndef INTERCOMMANDS_H_
#define INTERCOMMANDS_H_

#include "command.h"

class InterCommands {
 public:
  InterCommands(std::vector<Command> args);
  command_result execute();
 private:
  std::vector<Command> args_;
  command_result cd_command();
  command_result echo_command();
  command_result cp_command(bool preserve_all);
  command_result mv_command();
  std::string basename(const std::string& path);
};

#endif  // INTERCOMMANDS_H_