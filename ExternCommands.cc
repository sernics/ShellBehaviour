#include "ExternCommands.h"

#include <iostream>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

#define READ_END  0
#define WRITE_END 1

ExternCommands::ExternCommands(std::vector<Command> commands) : commands_(commands) {
  for (auto command : commands_) {
    if (command.size() == 1 && command[0] == "|") {
      pipe_size_++;
    }
  }
  std::cout << this->pipe_size_ << std::endl;
}

command_result ExternCommands::execute() {
  pid_t pid = fork();
  if (pid == 0) {
    auto command_split = this->split(0);
    execvp(command_split[0], command_split.data());
  } else {
    int status;
    waitpid(pid, &status, 0);
  }
  return command_result(0, 0);
}

std::vector<char*> ExternCommands::split(const int index) {
  std::vector<char*> args;
  for (int i{0}; i < this->commands_[index].size(); i++) {
    args.push_back(const_cast<char*>(this->commands_[index][i].c_str()));
  }
  args.push_back(NULL);
  return args;
}