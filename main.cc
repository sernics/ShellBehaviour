#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "shell.h"

int main() {
  Shell shell;
  int last_command_status = 0;
  shell.print_prompt(last_command_status);
  std::string line;
  int fd = 0;
  std::error_code error = shell.read_line(fd, line);
  auto commands = shell.parse_line(line);
  if (commands.size() > 0) {
    auto execute = shell.execute_command(commands);
    std::cout << execute.return_value << std::endl;
  }
  close(fd);
  return 0;
}
