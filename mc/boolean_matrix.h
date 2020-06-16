#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <fstream>

/**
 * @struct matrix
 * @brief Matriz booleana baseada em vectors
 */
class matrix : public std::vector<std::vector<bool>> {
public:

  // Modos de leitura: formatações de arquivos de grafos
  enum fmt { dimacs, orlibrary };

  /*
   * ctor padrão 
   * @param len tamanho da matriz
   * */
  matrix(uint len = 0)
  : std::vector< std::vector<bool> >(len, std::vector<bool>(len)) 
    {}

  /*
   * @brief Pega um valor nos dados índices de linha e coluna
   * @param i índice da linha
   * @param k índice da coluna
   */
  bool get(uint i, uint k) {
    return this->at(i).at(k);
  }

  /*
   * @brief Flipa um valor nos dados índices, se for 0 muda pra 1 e vice-versa
   * @param i índice da linha
   * @param k índice da coluna
   */
  void flip(uint i, uint k) {
    this->at(i).at(k) = !this->at(i).at(k);
    if (i != k)
      this->at(k).at(i) = !this->at(k).at(i);
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
  }

  /*
   * @brief Checa se um cromossomo define um clique
   * @param x o cromossomo para verificar
   */
  bool is_clique(const std::vector<bool>& x) {
    for (uint i = 0; i < x.size(); i++) {
      if (x[i]) {
        for (uint k = x.size()-1; k >= 0; k--) {
          if (x[k] and k != i) {
            if (this->get(i,k) == 0) {
              return false;
            }
          } else if (k == i) {
            break;
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
  static matrix *read_from_file(const char *filename, fmt mode = fmt::dimacs) {
    std::ifstream f(filename);
    char ch;
    std::string s;
    int V, E, u, v;

    f >> ch >> s >> V >> E;
    matrix *A = new matrix(V);

    while ( !f.eof() ) {
      f >> ch >> u >> v;
      if (ch == 'e') {
        A->set(u-1, v-1);
      }
    }
    return A;
  }
};

#endif //MATRIX_H_