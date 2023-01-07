#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

#include "InterCommnads.h"

InterCommands::InterCommands(std::vector<Command> args) : args_(args) {}

command_result InterCommands::execute() {
  if (args_[0][0] == "cd") {
    return this->cd_command().return_value;
  }
  if (args_[0][0] == "echo") {
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
  std::string src_path = std::string(this->args_[0][1]);
  std::string dest_path = std::string(this->args_[0][2]);
  struct stat src_stat;
  if (stat(src_path.c_str(), &src_stat) != 0) {
    return command_result(errno, 0);
  }
  if (!S_ISREG(src_stat.st_mode)) {
    return command_result(1, 0);
  }
  struct stat dest_stat;
  if (stat(dest_path.c_str(), &dest_stat) != 0) {
    if (src_stat.st_ino == dest_stat.st_ino &&
        src_stat.st_dev == dest_stat.st_dev) {
      return command_result(1, 0);
    }
  }
  if (S_ISDIR(dest_stat.st_mode)) {
    dest_path += "/";
    dest_path += src_path;
  }
  int src_fd = open(src_path.c_str(), O_RDONLY);
  if (src_fd == -1) {
    return command_result(errno, 0);
  }
  
}

command_result InterCommands::mv_command() {
  // TODO
}