#include <vector>
#include <string>
#include <system_error>

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

class Shell {
  public:
    Shell();
    void run();
    void print_prompt(int last_command_status);
    std::error_code read_line(int fd, std::string& line);
    std::vector<Command> parse_line(const std::string& line);
    command_result execute_command(const std::vector<Command>& commands);
    int execute_program(const std::vector<std::string>& args, bool has_wait=true);
  private:
    std::vector<uint8_t> pending_input_;
    
};
