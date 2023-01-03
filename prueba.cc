#include <algorithm>
#include <iostream>
#include <vector>
#include <system_error>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  // Leer los datos de input.txt con open y read
  int fd = open("input.txt", O_RDONLY);
  std::vector<uint8_t> input;
  uint8_t buffer[1024];
  int bytes_read = read(fd, buffer, 1024);
  // Comprobar si dio error
  if (bytes_read == -1) {
    std::cout << "Error al leer el archivo" << std::endl;
    return 1;
  }
  while (bytes_read > 0) {
    input.insert(input.end(), buffer, buffer + bytes_read);
    bytes_read = read(fd, buffer, 1024);
  }
  close(fd);
  for (auto& c : input) {
    std::cout << c;
  }
  std::cout << std::endl;
}