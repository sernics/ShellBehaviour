#include <vector>
#include <string>
#include <system_error>
#include "InterCommnads.h"

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
    // Funciones privadas
    bool are_commands_end(const std::string& input);
    bool are_commands_start(const std::string& input);
    bool is_a_commentary(const std::string& input);
    bool is_an_internal_command(const std::string& input);
    // Funcion para comandos externos
    int foo_command(const std::vector<Command>& args);
};
