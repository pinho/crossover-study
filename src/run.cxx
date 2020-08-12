/**
 * Executável para executar várias vezes os mesmo comando de 
 * sistema com os mesmos argumentos 
 */

#include <string>
#include <iostream>

int main(int argc, char **argv) {
  if (argc <= 1) {
    std::cout << "Arguments are required\n";
    return 1;
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
  } else {
    std::cout << "Command: ";
    std::getline(std::cin, command);
  }

  // fmt::print("Executando o comando \'{}\' {} vezes\n", command, number_executions);
  for (uint32_t n = 1; n <= number_executions; n++) {
    system(command.c_str());
  }

  return 0;
}

// void help() {
//   std::cout << "Executa um comando N vezes\n";
//   std::cout << "\nUsage: run [N] [COMMAND]\n";
//   std::cout << "\nWhere:\n";
//   std::cout << "  N       é o número de vezes para executar";
//   std::cout << "  COMMAND é o comando a ser repetido" << std::endl;
// }