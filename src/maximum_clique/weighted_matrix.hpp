#ifndef WEIGHTED_MATRIX_HPP_
#define WEIGHTED_MATRIX_HPP_

#include <fstream>
#include "boolean_matrix.h"

struct weighted_matrix : public matrix {
public:
  // ctor
  explicit weighted_matrix(unsigned int length = 0) : matrix(length) {
    this->weights = new int[length];
  }
  // dtor
  ~weighted_matrix() = default;

  // Métodos específicos

  // Pega o peso do vértice na posição "nodeidx"
  int get_weight(unsigned int nodeidx) {
    assert(nodeidx < this->num_nodes);
    return this->weights[nodeidx];
  }

  // Define o peso do vértice na posição "nodeidx"
  void set_weight(unsigned int nodeidx, int w) {
    assert(nodeidx < this->num_nodes);
    this->weights[nodeidx] = w;
  }

  static weighted_matrix read_file(std::ifstream &stream) {
    if (stream.is_open()) {
      char c;
      weighted_matrix *mat;
      while (!stream.eof()) {
        stream >> c;
        int n_nodes, n_edges;
        if (c == 'p') {
          std::string s;
          stream >> s >> n_nodes >> n_edges;
          mat = new weighted_matrix(n_nodes); // Cria a matrix com N vértices
        }
        else if (c == 'n') {
          int node, w;
          stream >> node >> w;
          mat->set_weight(node-1, w);
        }
        else if (c == 'e') {
          int i, k;
          stream >> i >> k;
          mat->set(i-1, k-1);
        }
        else if (c == 'c') {
          stream.ignore(512);
        }
      }
      stream.close();
      return *mat;
    } else throw std::runtime_error("read_file: Arquivo não aberto.");
  }

private:
  int *weights;
};

#endif