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
  int fd = open("input.txt", O_RDONLY);
  std::error_code error = shell.read_line(fd, line);
  std::cout << line << std::endl;
  return 0;
}
