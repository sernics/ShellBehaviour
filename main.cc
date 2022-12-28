#include <iostream>
#include <unistd.h>
#include "shell.h"

int main() {
  Shell shell;
  int last_command_status = 0;
  shell.print_prompt(last_command_status);
  return 0;
}
