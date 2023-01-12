#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "shell.h"

int main() {
  system("clear");
  int fd = 0;
  int last_command_status = 0;
  while (true) {
    Shell shell;
    shell.print_prompt(last_command_status);
    std::string line;
    std::error_code error = shell.read_line(fd, line);
    if (line == "exit\n") {
      break;
    }
    auto commands = shell.parse_line(line);
    if (commands.size() > 0) {
      auto execute = shell.execute_command(commands);
      last_command_status = execute.return_value;
      if (last_command_status < 0) {
        std::cout << "Error al ejecutar el comando anterior..." << std::endl;
      }
    }
  }
  close(fd);
  return 0;
}
