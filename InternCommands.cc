#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>

#include "InterCommnads.h"

InterCommands::InterCommands(std::vector<Command> args) : args_(args) {}

command_result InterCommands::execute() {
  if (args_[0][0] == "cd") {
    return this->cd_command().return_value;
  } else if (args_[0][0] == "echo") {
    return this->echo_command().return_value;
  } else if (args_[0][0] == "cp") {
    return this->cp_command(true).return_value;
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

command_result InterCommands::cp_command(bool preserve_all = false) {
  std::string src_path = args_[0][1];
  std::string dst_path = args_[0][2];
  struct stat src;
  struct stat dst;
  char buffer[1024];
  int fd1;
  int fd2;
  if (stat(src_path.c_str(), &src) == -1) {
    throw std::system_error(errno, std::system_category(),
                            "Error al obtener el estado del archivo src_path");
  }
  if (!S_ISREG(src.st_mode)) {
    throw std::system_error(errno, std::system_category(),
                            "El archivo no es un archivo regular");
  }
  if (stat(dst_path.c_str(), &dst) == -1) {
    dst_path += "/";
    dst_path += basename(src_path);
  }
  fd1 = open(src_path.c_str(), O_RDONLY);
  fd2 = open(dst_path.c_str(), O_WRONLY);
  if (stat(dst_path.c_str(), &dst) == -1) {
    fd2 = open(dst_path.c_str(), O_WRONLY | O_CREAT);
  } else {
    fd2 = open(dst_path.c_str(), O_WRONLY | O_TRUNC);
  }
  int numbytes = read(fd1, buffer, sizeof(buffer));
  while (numbytes > 0) {
    std::cout << numbytes << std::endl;
    write(fd2, buffer, numbytes);
    numbytes = read(fd1, buffer, sizeof(buffer));
  }
  if (preserve_all == true) {
    chmod(dst_path.c_str(), src.st_mode);
    chown(dst_path.c_str(), src.st_uid, src.st_gid);
    struct timespec times[2];
    times[0] = src.st_atim;
    times[1] = src.st_mtim;
    futimens(fd2, times);
  }
  close(fd1);
  close(fd2);
  return command_result(0, 0);
}

command_result InterCommands::mv_command() {
  struct stat src;
  struct stat dst;
  std::string src_path = args_[0][1];
  std::string dst_path = args_[0][2];
  std::string final_path;
  char buffer[1024];
  stat(dst_path.c_str(), &dst);
  if (stat(src_path.c_str(), &src) == -1) {
    throw std::system_error(errno, std::system_category(),
                            "Error al obtener el estado del archivo");
  }
  if (S_ISDIR(dst.st_mode)) {
    final_path = dst_path;
    final_path += basename(src_path.c_str());
  }
  if (src_path == dst_path) {
    rename(src_path.c_str(), final_path.c_str());
  } else {
    this->cp_command(false);
    unlink(src_path.c_str());
  }
  return command_result(0, 0);
}

std::string InterCommands::basename(const std::string &path) {
  std::array<char, PATH_MAX> buffer;
  path.copy(buffer.data(), buffer.size());
  return std::string(basename(buffer.data()));
}