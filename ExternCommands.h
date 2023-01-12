#ifndef EXTERNCOMMANDS_H_
#define EXTERNCOMMANDS_H_

#include "command.h"

class ExternCommands {
 public:
  // Constructor de comandos externos
  ExternCommands(std::vector<Command> commands);
  // Fncion de execute para comandos externos
  command_result execute();
  // Dividir el comando para poder pasarselo al execvp
  std::vector<char*> split(const int index);

 private:
  // Numero de pipes para poder hacerlo dinamico
  int pipe_size_ = 0;
  // Vector de comandos (std::vector<std::string>)
  std::vector<Command> commands_;
};

#endif  // EXTERNCOMMANDS_H_