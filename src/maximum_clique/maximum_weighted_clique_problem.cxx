#include "maximum_weighted_clique_problem.h"

MWCProblem::MWCProblem(const char *filepath) {
  // this->M = matrix::read_from_file(filepath);
  std::ifstream file(filepath);
  this->mat = weighted_matrix::read_file(file);
  this->__chromSize = mat.get_num_nodes();
  this->__name = (char *) "Problema do Clique Máximo";
  this->__acronym = (char *) "MCP";
  this->__minimize = false;
  this->__infilename = (char *)filepath;

  // Criar um vector para mapear os graus de cada nó
  degrees = std::vector<int>(__chromSize);
  for (size_t i = 0; i < (size_t)__chromSize; i++) {
    degrees[i] = std::accumulate( mat[i].begin(), mat[i].end(), 0 );
  }
}

MWCProblem::~MWCProblem() = default;

void MWCProblem::display_info(std::ostream &os) {
  os << __name << " (Maximização) " << std::endl;
  os << this->mat.get_num_nodes() << " vértices" << std::endl;
  os << this->mat.get_num_edges() << " arestas" << std::endl;
}

eoPop<Chrom> MWCProblem::init_pop(uint length, double bias) {
  return Random<Chrom>::population(__chromSize, length, bias);
}

// void MCProblem::repair_clique(Chrom& chromosome) {
//   assert(chromosome.size() == this->__chromSize);

//   // cria um novo vector com os vértices que estão na solução
//   std::vector<std::pair<int, int>> nodes_included;
//   for (uint i=0; i < __chromSize; i++)
//     if (chromosome[i]) nodes_included.emplace_back(i, 0);

//   count_adjacency(nodes_included, __graph);
//   // bool cont = !check_counting(nodes_included);

//   while ( !check_counting(nodes_included) ) {
//     // Ordenando os elementos [nó; grau]
//     std::sort(nodes_included.begin(), nodes_included.end(),
//         [](const auto &a, const auto &b) { return a.second < b.second; }
//     );

//     // eliminar o menor
//     chromosome[nodes_included.begin()->first] = 0;
//     nodes_included.erase( nodes_included.begin() );
//     // re-contagem
//     count_adjacency(nodes_included, __graph);
//   }
// }

/**
 * Repair Clique procura o vértice incluso na solução que tem o menor grau,
 * e o remove. */
void MWCProblem::repair_clique(Chrom& chrom) {
  while (!mat.is_clique(chrom)) {
    int index;
    int minor = std::numeric_limits<int>::max();
    
    for (size_t i = 0; i < __chromSize; i++) {
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


double MWCProblem::objective_function(Chrom &chrom) {
  repair_clique(chrom);
  random_generator<int> rg(__chromSize);
  int r = rg();
  expand_clique(chrom, r);

  if (mat.is_clique(chrom)) {
    int sum = 0;
    for (size_t i=0; i < chrom.size(); i++) {
      sum += chrom[i] * mat.get_weight(i);
    }
    return sum;
  } else {
    return 0;
  }
}
