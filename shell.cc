#include "shell.h"

#include <pwd.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <sstream>

Shell::Shell() = default;

void Shell::print_prompt(int last_command_status) {
  char* username = getpwuid(getuid())->pw_name;
  char* hostname = new char[1024];
  char* cwd = new char[1024];
  gethostname(hostname, 1024);
  getcwd(cwd, 1024);
  std::cout << username << "@" << hostname << ":" << cwd;
  if (last_command_status == 0) {
    std::cout << " $> ";
  } else {
    std::cout << " $< ";
  }
  std::cout << std::endl;
}

std::error_code Shell::read_line(int fd, std::string& line) {
  while (true) {
    auto line_jump = std::find(pending_input_.begin(), pending_input_.end(), '\n');
    if (line_jump != pending_input_.end()) {
      int line_jump_position = line_jump - pending_input_.begin();
      for (int i{0}; i <= line_jump_position; i++) {
        line.push_back(pending_input_[i]);
      }
      pending_input_.erase(pending_input_.begin(), line_jump + 1);
      return std::error_code(0, std::generic_category());
    }
    uint8_t buffer[1024];
    int bytes_read = read(fd, buffer, 1024);
    if (bytes_read == -1) {
      return std::error_code(errno, std::generic_category());
    }
    // Comprobar el tamaño del buffer
    if (bytes_read == 0) {
      if (pending_input_.size() != 0) {
        for (const auto c : pending_input_) {
          line.push_back(c);
        }
        line.push_back('\n');
        pending_input_.clear();
      }
      return std::error_code(0, std::generic_category());
    } else {
      for (int i{0}; i < bytes_read; i++) {
        pending_input_.push_back(buffer[i]);
      }
    }
  }
}