#include "steiner_tree.h"

SteinerTreeProblem::SteinerTreeProblem(const char* filename) {
  this->instanceFilename = (char*) filename;
  this->minimization = true;

  // Ler o arquivo de texto
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string* file_content = new std::string(
      std::istreambuf_iterator<char>(file),
      std::istreambuf_iterator<char>()
    );
    std::vector<std::string> file_content_vec = split(*file_content, ' ');
    std::vector<float> file_content_numbers = convert_vec(file_content_vec);
    file.close();

    // Lendo as quantidades e tamanhos
    uint index = 0;
    this->num_nodes = file_content_numbers[index++]; // 0 -> 1
    this->num_edges = file_content_numbers[index++]; // 1 -> 2
    // this->num_steiner_nodes = file_content_numbers[2 + 3*num_edges];

    // Criação dos arrays
    this->nodes_vec_ptr = new std::vector<int>(num_nodes);
    this->weights_vec_ptr = new std::vector<float>();
    this->edges_vec_ptr = new std::vector<edge_t>();

    // Atribuindo os valores aos arrays de arestas e pesos
    for (; index < this->num_edges*3; index+=3) {
      this->edges_vec_ptr->emplace_back(
        edge_t(file_content_numbers[index], file_content_numbers[index+1])
      );
      this->weights_vec_ptr->emplace_back(file_content_numbers[index+2]);
    }

    // Atribuindo os valores do array de vértices de Steiner
    // index += 1; // pula o número de vértices de Steiner (já foi lido)
    this->num_steiner_nodes = file_content_numbers[index];
    std::cout << "num_steiner_nodes = " << this->num_steiner_nodes << "\n";
    this->steiner_nodes_vec_ptr = new std::vector<int>(num_steiner_nodes);
    this->chromSize = this->num_steiner_nodes;
    index += 1;

    for (size_t i=0; i < this->steiner_nodes_vec_ptr->size(); i++) {
      this->steiner_nodes_vec_ptr->at(i) = file_content_numbers[index];
      index++;
    }
  }
}

SteinerTreeProblem::~SteinerTreeProblem() {
  free(this->nodes_vec_ptr);
  free(this->steiner_nodes_vec_ptr);
  free(this->weights_vec_ptr);
  free(this->edges_vec_ptr);
}

eoPop<Chrom> SteinerTreeProblem::init_pop(uint len, double bias) {
  return Random<Chrom>::population(this->chromSize, len, bias);
}

void SteinerTreeProblem::operator()(Chrom& chromosome) {
  std::vector<edge_t> edges(*this->edges_vec_ptr);
  std::vector<float> weights(*this->weights_vec_ptr);
  int num_removed_nodes = 0;

  for (uint i=0; i < this->chromSize; i++) {
    if (!chromosome[i]) {
      remove_node(edges, weights, this->steiner_nodes_vec_ptr->at(i));
      num_removed_nodes++;
    }
  }
  int V = this->num_nodes - num_removed_nodes;
  auto&& [mst_edges, mst_cost] = KruskalMST(V, num_edges, &edges[0], &weights[0]);

  chromosome.fitness(1 / mst_cost);
}

void
SteinerTreeProblem::remove_node(std::vector<edge_t>& edges,
    std::vector<float>& weights, int node)
{
  for (std::size_t i=0; i < edges.size(); i++) {
    if (edges[i].first == node or edges[i].second == node) {
      edges.erase(edges.begin()+i);
      weights.erase(weights.begin()+i);
      i--;
    }
  }
}

std::vector<int> *const SteinerTreeProblem::steiner_nodes() {
  return this->steiner_nodes_vec_ptr;
}
