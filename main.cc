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
  std::cout << commands.size() << std::endl;
  std::cout << "Commands:" << std::endl;
  for (const auto command_palette : commands) {
    for (const auto command : command_palette) {
      std::cout << command << " ";
    }
    std::cout << std::endl;
  }
  if (commands.size() > 0) {
    auto execute = shell.execute_command(commands);
  }
  close(fd);
  return 0;
}
