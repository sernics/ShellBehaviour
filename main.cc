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
  std::error_code error = shell.read_line(0, line);
  std::cout << line.size() << std::endl;
  for (const auto el : line) {
    if (el == '\n') {
      std::cout << "-";
    } else {
      std::cout << el;
    }
  }
  std::cout << std::endl;
  return 0;
}
