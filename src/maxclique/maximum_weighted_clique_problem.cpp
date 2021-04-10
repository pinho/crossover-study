#include "maximum_weighted_clique_problem.h"

MWCProblem::MWCProblem(const char *filepath) {
  std::ifstream file(filepath);
  this->mat = weighted_matrix::read_file(file);
  this->chromSize = mat.get_num_nodes();
  this->minimization = false;
  this->instanceFilename = (char *)filepath;

  // Criar um vector para mapear os graus de cada nó
  degrees = std::vector<int>(this->chromSize);
  for (size_t i = 0; i < (size_t)this->chromSize; i++) {
    degrees[i] = std::accumulate( mat[i].begin(), mat[i].end(), 0 );
  }
}

MWCProblem::~MWCProblem() = default;

eoPop<Chrom> MWCProblem::init_pop(uint length, double bias) {
  return Random<Chrom>::population(this->chromSize, length, bias);
}

/**
 * Repair Clique procura o vértice incluso na solução que tem o menor grau,
 * e o remove. */
void MWCProblem::repair_clique(Chrom& chrom) {
  while (!mat.is_clique(chrom)) {
    int index;
    int minor = std::numeric_limits<int>::max();
    
    for (size_t i = 0; i < this->chromSize; i++) {
      if (chrom[i] and degrees[i] < minor) {
        minor = degrees[i]; index=i;
      }
    } 
    chrom[index] = 0;
  }
}


void MWCProblem::expand_clique(Chrom& chrom, uint gene_index) {
  assert(gene_index < chrom.size());
  // Pré-processamento:
  // Índices dos vértices presentes e não presentes na solução
  // são armazenados em vectors separados para controle
  std::vector<int> included, excluded;
  for (size_t i = 0; i < chrom.size(); i++) {
    if (chrom[i]) {
      included.push_back(i);
    } else if (i >= gene_index) {
      excluded.push_back(i);
    }
  }

  // Pra cada vértice que não está incluído na solução,
  // é vericado se ele está conectado a todos os vértices incluídos
  // para então adicioná-lo.
  for (int v : excluded) {
    bool add = true;
    for (int u : included) {
      if (!mat[v][u] and v != u) {
        add = false;
        break;
      }
    }
    if (add) {
      chrom[v] = 1; // add this node in chromosome
      included.push_back(v); // add on the included vector
    }
  }
}


void MWCProblem::operator()(Chrom &chrom) {
  repair_clique(chrom);
  random_generator<int> rg(this->chromSize);
  int r = rg();
  expand_clique(chrom, r);

  if (mat.is_clique(chrom)) {
    int sum = 0;
    for (size_t i=0; i < chrom.size(); i++) {
      sum += chrom[i] * mat.get_weight(i);
    }
    chrom.fitness(sum);
  } else {
    chrom.fitness(0);
  }
}
