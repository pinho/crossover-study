#include "options.h"
#include "parse.h"

option long_options[] = {
  { "infile",    required_argument, 0, 'f' },
  { "db",        required_argument, 0, 'd' },
  { "popsize",   required_argument, 0, 'p' },
  { "epochs",    required_argument, 0, 'g' },
  { "crossover", required_argument, 0, 'x' },
  { "xrate",     required_argument, 0, 'c' },
  { "mrate",     required_argument, 0, 'm' },
  { "ring",      required_argument, 0, 'r' },
  { "help",      no_argument, 0, 'h' },
  { 0, 0, 0, 0 }
};

const char *short_options = "f:d:p:g:x:c:m:r:h";

const unsigned int NUM_OPTIONS = 9;

const char *DESC[NUM_OPTIONS] = {
    "Arquivo de instância do problema",
    "Arquivo .db para salvar os dados. Se não definido não salva",
    "Tamanho da população [default = 100]",
    "Número de épocas/gerações [default = 100]",
    "Operador de crossover utilizado com um ID [default = 0]",
    "Taxa de cruzamento (%) [default = 0.8]",
    "Taxa de mutação (%) [default = 0.05]",
    "Tamanho do Ring do operador de seleção por torneio determinístico [default = 8]",
    "Mostra essa lista de opções"
};

void show_help(char **argv) {
  printf("Use: %s -f [input-file] [ARGS] ...\n", argv[0]);
  
  printf("ARGS:\n");
  for (unsigned int i = 0; i < NUM_OPTIONS; i++) {
    if (long_options[i].name) {
      if (long_options[i].val) {
        printf("  -%c, --%-10s  %s\n", long_options[i].val, long_options[i].name, DESC[i]);
      } else {
        printf("      --%-10s  %s\n", long_options[i].name, DESC[i]);
      }
    }
  }
}

CLI *parse(int argc, char **argv) {
  CLI* res = new CLI();
  int opt;
  while ((opt = getopt_long(argc,argv, short_options,long_options,0)) != -1) {
    switch (opt) {
      case 'd':
        if (optarg) {
          res->databasefile = optarg;
          res->using_db = true;
        }
        break;
      case 'f':
        if (optarg) res->infile = optarg;
        break;
      case 'p':
        if (optarg) res->pop_size = std::stoi(optarg);
        break;
      case 'g':
        if (optarg) res->epochs = std::stoi(optarg);
        break;
      case 'c':
        if (optarg) res->crossover_rate = std::stod(optarg);
        break;
      case 'm':
        if (optarg) res->mutation_rate = std::stod(optarg);
        break;
      case 'x':
        if (optarg) res->crossover_id = std::stoi(optarg);
        break;
      case 'r':
        if (optarg) res->tour_size = std::stoi(optarg);
        break;
      case 'h':
        show_help(argv);
        exit(127);
      default:
        printf("Use -h ou --help para ver as opções de linha de comandos.\n");
        exit(2);
    }
  }

  return res;
}


std::string identify(CLI& cli) {
  std::string ID;

  if (cli.crossover_rate > 1 || cli.crossover_rate < 0) {
    cli.crossover_rate = 1;
  }

  if (cli.mutation_rate > 1 || cli.mutation_rate < 0) {
    cli.mutation_rate = 0.05;
  }

  ID = cli.crossover_id == 0? "UNIFORM" : std::to_string(cli.crossover_id).append("POINTS");
  // P(popsize)
  ID.append("P").append(std::to_string(cli.pop_size));
  // G(epochs)
  ID.append("G").append(std::to_string(cli.epochs));
  // CR(crossover_rate)
  ID.append("CR");
  auto cr = std::to_string(cli.crossover_rate);
  cr.erase(cr.begin()+1);
  cr.erase(cr.begin()+3, cr.end());
  ID.append(cr);
  // MR(mutation_rate)
  ID.append("MR");
  auto mr = std::to_string(cli.mutation_rate);
  mr.erase(mr.begin()+1);
  mr.erase(mr.begin()+3, mr.end());
  ID.append(mr);
  
  return ID;
}
