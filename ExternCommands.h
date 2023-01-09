#include <vector>
#include <string>
#include <iostream>
#include "command.h"

class ExternCommands {
  public:
   ExternCommands(std::vector<Command> commands);
    void execute();
  private:
   int pipe_size_;
   std::vector<std::string> commands_;

};