#ifndef EXTERNCOMMANDS_H_
#define EXTERNCOMMANDS_H_

#include "command.h"

class ExternCommands {
 public:
  ExternCommands(std::vector<Command> commands);
  command_result execute();
  std::vector<char*> split(const int index);

 private:
  int pipe_size_ = 0;
  std::vector<Command> commands_;
};

#endif  // EXTERNCOMMANDS_H_