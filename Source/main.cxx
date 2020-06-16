#include <iostream>
#include <vector>
#include <string>

#include "args.hxx"
#include "problems.hxx"
using namespace args;

int main(int argc, char **argv) {
  ArgumentParser p("Estudos de crossovers");
  Group commands(p, "Problemas");
  Command clique(commands, "mc", "Clique máximo");
  Command steiner(commands, "st", "Árvore de Steiner");
  Command scp(commands, "sc", "Cobertura de conjuntos");
  Command mknap(commands, "mk", "Mochila multi-dimensional");
  HelpFlag h(p, "help", "Help menu", {'h', "help"});

  try {
    p.ParseCLI(argc, argv);
  } catch(Help) {
    std::cout << p;
  } catch (args::Error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  // transformando argumentos em um vector
  std::vector<char *> vec_args;
  for (int i=0; i < argc; i++) {
    vec_args.push_back( argv[i] );
  }
  // pegando somente o primeiro argumento após o nome do programa
  std::string problem_name = vec_args[1];
  vec_args.erase(vec_args.begin()+1);
  char **newArgs = &vec_args[0];
  int newArgc = vec_args.size();

  if (clique) {
    problem::max_clique(newArgc, newArgs);
  } else if (steiner) {
    problem::steiner_tree(newArgc, newArgs);
  } else if (scp) {
    problem::set_covering(newArgc, newArgs);
  } else if (mknap) {
    problem::multi_knap(newArgc, newArgs);
  }

  return 0;
}
