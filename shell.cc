#include "shell.h"

#include <pwd.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>

#include "ExternCommands.h"

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
  std::cout << std::flush;
}

std::error_code Shell::read_line(int fd, std::string& line) {
  while (true) {
    auto line_jump =
        std::find(pending_input_.begin(), pending_input_.end(), '\n');
    if (line_jump != pending_input_.end()) {
      int line_jump_position = line_jump - pending_input_.begin();
      for (int i{0}; i <= line_jump_position; i++) {
        line.push_back(pending_input_[i]);
      }
      pending_input_.erase(pending_input_.begin(), line_jump + 1);
      return std::error_code(0, std::generic_category());
    }
    const int BufferSize = 1024;
    uint8_t buffer[BufferSize];
    int bytes_read = read(fd, buffer, BufferSize);
    if (bytes_read == -1) {
      return std::error_code(errno, std::generic_category());
    }
    if (bytes_read == 0) {
      if (line.empty()) {
        return std::error_code(0, std::generic_category());
      } else {
        if (pending_input_.size() != 0) {
          for (const auto c : pending_input_) {
            line.push_back(c);
          }
          line.push_back('\n');
          pending_input_.clear();
        }
        return std::error_code(0, std::generic_category());
      }
    } else {
      for (int i{0}; i < bytes_read; i++) {
        pending_input_.push_back(buffer[i]);
      }
    }
  }
}

std::vector<Command> Shell::parse_line(const std::string& line) {
  std::vector<Command> commands;
  std::istringstream iss(line);
  Command command_palette;
  while (!iss.eof()) {
    std::string input;
    iss >> input;
    if (input == ";" || input == "&" || input == "|") {
      commands.push_back(command_palette);
      commands.push_back({input});
      command_palette.clear();
    } else if (input == "#") {
      commands.push_back(command_palette);
      command_palette.clear();
      return commands;
    } else if (input.empty()) {
      if (this->are_commands_end(input)) {
        std::string last_item = std::string(1, input[input.size() - 1]);
        input.resize(input.size() - 1);
        command_palette.push_back(input);
        commands.push_back(command_palette);
        command_palette.clear();
        commands.push_back({last_item});
      } else if (this->are_commands_start(input)) {
        commands.push_back(command_palette);
        command_palette.clear();
        std::string first_item = std::string(1, input[0]);
        input.erase(input.begin());
        commands.push_back({first_item});
        commands.push_back({input});
      } else if (this->is_a_commentary(input)) {
        commands.push_back(command_palette);
        command_palette.clear();
      } else {
        commands.push_back(command_palette);
        command_palette.clear();
      }
    } else {
      if (this->are_commands_end(input)) {
        std::string last_item = std::string(1, input[input.size() - 1]);
        input.resize(input.size() - 1);
        command_palette.push_back(input);
        commands.push_back(command_palette);
        commands.push_back({last_item});
        command_palette.clear();
      } else if (this->are_commands_start(input)) {
        commands.push_back(command_palette);
        command_palette.clear();
        std::string first_item = std::string(1, input[0]);
        input.erase(input.begin());
        commands.push_back({first_item});
        command_palette.push_back(input);
      } else if (this->is_a_commentary(input)) {
        commands.push_back(command_palette);
        command_palette.clear();
        return commands;
      } else {
        command_palette.push_back(input);
      }
    }
  }
  for (int i{0}; i < commands.size(); i++) {
    if (commands[i].size() == 0) {
      commands.erase(commands.begin() + i);
    }
  }
  return commands;
}

command_result Shell::execute_command(const std::vector<Command>& commands) {
  std::string command = "";
  for (const auto& item : commands) {
    for (const auto command_part : item) {
      command += command_part;
      command += " ";
    }
  }
  if (this->is_an_internal_command(command)) {
    return command_result(this->foo_command(commands), 0);
  } else {
    ExternCommands external_command(commands);
    return external_command.execute();
  }
  return command_result(0, 0);
}

bool Shell::are_commands_end(const std::string& input) {
  if (input[input.size() - 1] == ';' || input[input.size() - 1] == '&' ||
      input[input.size() - 1] == '|') {
    return true;
  }
  return false;
}

bool Shell::are_commands_start(const std::string& input) {
  if (input[0] == ';' || input[0] == '&' || input[0] == '|') {
    return true;
  }
  return false;
}

bool Shell::is_a_commentary(const std::string& input) {
  if (input[0] == '#') {
    return true;
  }
  return false;
}

bool Shell::is_an_internal_command(const std::string& command) {
  std::regex echo_regex("^echo\\s+(.*)$");
  std::regex cd_regex("^cd\\s+(.*)$");
  std::regex cp_regex("cp\\s+(-r\\s+)?(.*?)\\s+(.*?)$");
  std::regex mv_regex("^mv\\s+(.*?)\\s+(.*?)$");
  if (std::regex_match(command, echo_regex) ||
      std::regex_match(command, cd_regex) ||
      std::regex_match(command, cp_regex) ||
      std::regex_match(command, mv_regex)) {
    return true;
  }
  return false;
}

int Shell::foo_command(const std::vector<Command>& commands) {
  InterCommands inter_commands(commands);
  return inter_commands.execute().return_value;
}