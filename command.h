#include <vector>
#include <string>

using Command = std::vector<std::string>;

struct command_result {
  int return_value;
  bool is_quit_requested;

  command_result(int return_value, bool request_quit=false)
    : return_value(return_value),
      is_quit_requested(request_quit) 
  {}

  static command_result quit(int return_value=0) {
    return command_result(return_value, true);
  }
};