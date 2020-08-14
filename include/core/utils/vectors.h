
#ifndef UTILS_VECTORS_H
#define UTILS_VECTORS_H

#include <vector>
#include <string>
#include <iostream>

/**
 * Converter um vector de strings para um vector de floats
 */
std::vector<float> convert_vec(std::vector<std::string>& source);

template <typename T>
void print_vec(std::vector<T> &vec, std::ostream &os) {
  os << "[ ";
  for (T& elem : vec)
    os << elem << " ";
  os << "]" << std::endl;
}


#endif
