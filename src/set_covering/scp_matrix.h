#ifndef CROSSOVERSTUDY_SCP_MATRIX_H
#define CROSSOVERSTUDY_SCP_MATRIX_H 1

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>
#include <core/utils/split.h>

#define ASSERT_THROW(expr, onFailedMsg) \
  if ((expr) == false) throw std::runtime_error(onFailedMsg)

// namespace scp {
  struct matrix {
    size_t num_rows, num_columns;

  public:
    /**
     * Construtor padrão (NxM) */
    explicit matrix(size_t num_rows, size_t num_columns);

    /**
     * @brief Construtor a partir de um arquivo de entrada
     * @p inputfile instancia do arquivo de entrada */
    matrix(std::ifstream& inputfile);

    bool get(size_t i, size_t k);
    void set(size_t i, size_t k);
    void flip(size_t i, size_t k);
    float get_weight(size_t k);
    void set_weight(size_t k, float value);
    float* get_weights_pointer();

    friend std::ostream& operator<<(std::ostream &os, matrix &m);

  private:
    bool *values;
    float *weights;
  };
// }

#endif