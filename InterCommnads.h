#include "command.h"

class InterCommands {
  public:
    InterCommands(std::vector<Command> args);
    command_result execute();
  private:
    std::vector<Command> args_;
    command_result cd_command();
    command_result echo_command();
};