#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <fstream>

/**
 * @struct matrix
 * @brief Matriz booleana baseada em vectors
 */
struct matrix : public std::vector<std::vector<bool>> {
public:

  // Modos de leitura: formatações de arquivos de grafos
  enum fmt { dimacs, networkrepo };

  /*
   * ctor padrão 
   * @param len tamanho da matriz
   * */
  matrix(uint len = 0)
  : std::vector< std::vector<bool> >(len, std::vector<bool>(len)), num_nodes(len),
    num_edges(0) {}

  /*
   * @brief Pega um valor nos dados índices de linha e coluna
   * @param i índice da linha
   * @param k índice da coluna
   */
  bool get(uint i, uint k) {
    return this->at(i).at(k);
  }

  /*
   * @brief Seta um valor nos dados índices para 1
   * @param i índice da linha
   * @param k índice da coluna
   */
  void set(uint i, uint k) {
    this->at(i).at(k) = true;
    if (i != k)
      this->at(k).at(i) = true;
    this->num_edges++;
  }

  /**
   * Getters
   */
  unsigned int get_num_edges() {
    return num_edges;
  }

  unsigned int get_num_nodes() {
    return num_nodes;
  }

  /*
   * @brief Checa se um cromossomo define um clique
   * @param x o cromossomo para verificar
   */
  bool is_clique(const std::vector<bool>& x) {
    for (size_type i = 0; i < x.size(); i++) {
      if (x[i]) {
        for (size_type k = x.size()-1; k != i; k--) {
          if (x[k] and k != i) {
            if (this->get(i,k) == 0) {
              return false;
            }
          }
        }
      }
    }
    return true;
  }

  /*
   * @brief Ler arquivo de grafo e gerar uma instância de matrix de adjacências
   * @param filename nome do arquivo para ler 
   * @return um ponteiro para a nova matriz alocada
   */
  static matrix read_from_file(const char *filename, fmt mode = fmt::dimacs) {
    std::ifstream f(filename);
    char ch;
    std::string s;
    uint64_t V, E, u, v;
    matrix A;

    // Para o formato de arquivo do DIMACS
    if (mode == fmt::dimacs) {

      while ( !f.eof() ) {
        f >> ch;
        if (ch == 'c') {
          f.ignore(256, '\n');
        } else if (ch == 'p') {
          f >> s >> V >> E;
          A = matrix(V);
        } else if (ch == 'e') {
          f >> u >> v;
          A.set(u-1, v-1);
        } else {
          f.ignore(256, '\n');
        }
        ch = -1;
      }
      f.close();
      return A;
    }

    // Para o formato de arquivos do networkrepository.com
    else if (mode == fmt::networkrepo) {
      bool qtd_was_read = false;
      
      while ( !f.eof() ) {
        f >> ch;
        if (ch == '%') {
          f.ignore(256, '\n');
        } else if (!qtd_was_read) {
          f >> s >> V >> E;
          A = matrix(V);
        } else {
          f >> u >> v;
          A.set(u-1, v-1);
        }
        ch = -1;
      }
      f.close();
      return A;
    }

    return A;
  }

protected:
  unsigned int num_nodes;
  unsigned int num_edges;
};

#endif //MATRIX_H_