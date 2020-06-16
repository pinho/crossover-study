#ifndef PROBLEMS_HXX
#define PROBLEMS_HXX

/**
 * Definições das funções principais.
 * Cada função é como a função main() de cada problema abordado na pesquisa,
 * isso permite que eles possam ser executados através da mesma ferramenta e 
 * possam ter suas próprias implementações independentes.
 */
namespace problem {
  void max_clique(int argc, char **argv);
  void steiner_tree(int argc, char **argv);
  void set_covering(int argc, char **argv);
  void multi_knap(int argc, char **argv);
}

#endif