#ifndef SHELL_H_
#define SHELL_H_

#include <string>
#include <system_error>
#include <vector>

#include "ExternCommands.h"
#include "InterCommnads.h"

class Shell {
 public:
  // Constructor de shell
  Shell();
  // Funcion para imprimir el promt de nuestro usuario
  void print_prompt(int last_command_status);
  // Función para leer la información que el usuario introduzca
  std::error_code read_line(int fd, std::string& line);
  // Funcion para parsear el codigo que el usuario introduzca (pudiendo asi
  // tener un std::vector<Command>)
  std::vector<Command> parse_line(const std::string& line);
  // Funcion que ejecuta el comando introducido por el usuario
  command_result execute_command(const std::vector<Command>& commands);

 private:
  // Vector que se usa para el read line
  std::vector<uint8_t> pending_input_;
  // Funciones privadas ------
  // Funciones para saber si empieza o termina con alguno de estos caracteres
  // "&", "|", ";"
  bool are_commands_end(const std::string& input);
  bool are_commands_start(const std::string& input);
  // Funcion para saber si es un comentario
  bool is_a_commentary(const std::string& input);
  // Funcion para saber si lo introducido es un comando interno
  bool is_an_internal_command(const std::string& input);
};

#endif  // SHELL_H_