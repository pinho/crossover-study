#ifndef CROSSOVERSTUDY_SC_SUBSET_H
#define CROSSOVERSTUDY_SC_SUBSET_H

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstddef>

/**
 * A struct subset representa um subconjunto que pode ser escolhido
 * para compor uma solução do problema, em outras palavras é um linha da
 * matriz de cobertura. */
struct subset {
  const size_t len;
  const size_t universe_size;
  float weight;
  bool *values;

  // Recebe o peso (weight) do subconjunto, os valores do subconjunto e o
  // tamanho do conjunto universo
  explicit subset(float weight, std::vector<int> *vec_ptr, const size_t univ_set_size);

  // Operador de saída com ostream
  friend std::ostream& operator<<(std::ostream& os, const subset& s);
};

#endif