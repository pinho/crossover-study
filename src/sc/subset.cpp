#include "subset.h"

subset::subset(float weight, std::vector<int> *vec_ptr, const size_t univ_set_size)
  : len((const size_t) vec_ptr->size()), universe_size(univ_set_size)
{
  this->weight = weight;
  this->values = new bool[this->universe_size];
  for (unsigned int i=0; i < universe_size; i++) {
    this->values[i] = false;
  }
  for (unsigned int i=0; i < len; i++) {
    int index = vec_ptr->at(i) - 1;
    this->values[index] = true;
  }
}

std::ostream& operator<<(std::ostream& os, const subset& s) {
  char *buff = new char[100];
  sprintf(buff, "%i  %.3f  ", s.len, s.weight);
  os << buff;
  for (int i=0; i < s.universe_size; i++) {
    os << s.values[i] << " ";
  }
  free(buff);
  return os;
}
