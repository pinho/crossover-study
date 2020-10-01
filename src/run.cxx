/**
 * Executável para executar várias vezes os mesmo comando de 
 * sistema com os mesmos argumentos 
 */

#include <string>
#include <cstring>
#include <iostream>

int main(int argc, char **argv) {
  if (argc <= 1) {
    std::cout << "Arguments are required\n";
    return 1;
  }

  bool quiet = false;
  for (int i=1; i < argc; i++) {
    if (strcmp(argv[i], "--quiet") == 0) {
      quiet = true;
    }
  }

  std::string arg1(argv[1]);
  std::string command;
  uint32_t number_executions;

  try {
    number_executions = std::stoul(arg1);
  } catch (std::exception& e) {
    std::cout << "First argument should be an unsigned integer\n";
    return 1;
  }

  if (argc > 2) {
    for (int i=2; i < argc; i++) {
      command.append(argv[i]).append(" ");
    }
    if (quiet) {
      command.append(" 1> /dev/null");
    }
  } else {
    std::cout << "Command: ";
    std::getline(std::cin, command);
  }

  for (uint32_t n = 1; n <= number_executions; n++) {
    system(command.c_str());
  }

  return 0;
}
