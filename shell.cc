#include "shell.h"
#include <sstream>
#include <unistd.h>
#include <iostream>

Shell::Shell() = default;

void Shell::print_prompt(int last_command_status) {
  char* username;
  char* hostname = new char[1024];
  char* cwd = new char[1024];
  gethostname(hostname, 1024);
  getcwd(cwd, 1024);
  std::cout << "$" << username << "@" << hostname << ":" << cwd;
  if (last_command_status == 0) {
    std::cout << "> ";
  } else {
    std::cout << "< ";
  }
  std::cout << std::endl;
  if (getlogin()) {
    std::cout << "No da error" << std::endl;
  } else {
    std::cout << "Da error" << std::endl;
  }
}

std::error_code Shell::read_line(int fd, std::string& line) {
  while (true) {
    for (int i{0}; i < pending_input_.size(); i++) {
      if (pending_input_[i] == '\n') {
        for (int j{0}; j <= i; j++) {
          line.push_back(pending_input_[j]);
          pending_input_.erase(pending_input_.begin());
        }
        return std::error_code(0, std::system_category());
      }
    }
    auto error = read(fd, pending_input_.data(), pending_input_.size());
    if (error == -1) {
      return std::error_code(errno, std::system_category());
    }
    if (/*buffer vacio*/) {
      if (!pending_input_.empty()) {
        for (int i{0}; i < pending_input_.size(); i++) {
          line.push_back(pending_input_[i]);
        }
        line.push_back('\n');
        pending_input_.clear();
      }
      return std::error_code(0, std::system_category());
    } else {
      // Añadir el contenido del buffer al final de pending_input 
      read(fd, pending_input_.data(), pending_input_.size());
    }
  }
}