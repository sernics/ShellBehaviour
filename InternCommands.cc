#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <array>
#include <limits.h>

#include <iostream>

#include "InterCommnads.h"

InterCommands::InterCommands(std::vector<Command> args) : args_(args) {}

command_result InterCommands::execute() {
  if (args_[0][0] == "cd") {
    return this->cd_command().return_value;
  } else if (args_[0][0] == "echo") {
    return this->echo_command().return_value;
  } else if (args_[0][0] == "cp") {
    return this->cp_command().return_value;
  } else if (args_[0][0] == "mv") {
    return this->mv_command().return_value;
  } else {
    return command_result(-1, 0);
  }
}

command_result InterCommands::cd_command() {
  int exit_code = chdir(args_[0][1].c_str());
  return command_result(exit_code, 0);
}

command_result InterCommands::echo_command() {
  std::string result = "";
  for (int i{1}; i < this->args_[0].size(); i++) {
    result += this->args_[0][i];
    result += " ";
  }
  std::cout << result << std::endl;
  return command_result(0, 0);
}

command_result InterCommands::cp_command() {
  std::string src_path = args_[0][1];
  std::string dst_path = args_[0][2];
  struct stat src;
  struct stat dst;
  char buffer[1024];
  if (stat(src_path.c_str(), &src) == -1) {
    throw std::system_error(errno, std::system_category(),
                            "Error al obtener el estado del archivo src_path");
  }
  if (!S_ISREG(src.st_mode)) {
    throw std::system_error(errno, std::system_category(),
                            "El archivo no es un archivo regular");
  }
  if (stat(dst_path.c_str(), &dst) != -1) {
    assert(dst_path != src_path);
    if (S_ISDIR(dst.st_mode)) {
      dst_path += "/";
      dst_path += this->basename(src_path);
    }
  }
  int fd1 = open(src_path.c_str(), O_RDONLY);
  int fd2 = open(dst_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, src.st_mode);
  std::cout << src_path << std::endl;
  std::cout << dst_path << std::endl;
  int numbytes = read(fd1, buffer, sizeof(buffer));
  while (numbytes > 0) {
    std::cout << numbytes << std::endl;
    write(fd2, buffer, numbytes);
    numbytes = read(fd1, buffer, sizeof(buffer));
  }
  close(fd1);
  close(fd2);
}

command_result InterCommands::mv_command() {
  std::cout << "Move: " << std::endl;
  return command_result(-1, 0);
}

std::string InterCommands::basename(const std::string &path) {
  std::array<char, PATH_MAX> buffer;
  path.copy(buffer.data(), buffer.size());
  return std::string(basename(buffer.data()));
}