#ifndef INTERCOMMANDS_H_
#define INTERCOMMANDS_H_

#include "command.h"

class InterCommands {
 public:
  // Constructor de comandos internos
  InterCommands(std::vector<Command> args);
  // Ejecutar comandos internos
  command_result execute();

 private:
  // Argumentos de los comandos internos
  std::vector<Command> args_;
  // Funcion para cd
  command_result cd_command();
  // Funcion para echo
  command_result echo_command();
  // Funcion para cp
  command_result cp_command(bool preserve_all);
  // Funcion para mv
  command_result mv_command();
  // Funcion que usa cp para poder cambiar el nombre de un archivo cuando nos
  // referimos a una carpeta
  std::string basename(const std::string& path);
};

#endif  // INTERCOMMANDS_H_