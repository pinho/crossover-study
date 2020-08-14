#include "vectors.h"

/**
 * Converter um vector de strings para um vector de floats
 */
std::vector<float> convert_vec(std::vector<std::string>& source) {
  using Str = std::string;
  auto *target = new std::vector<float>;
  try {
    for (auto &string_element : source) {
      if (string_element != Str("\n") and string_element != Str(" ")) {
        target->push_back( std::stof(string_element) );
      }
    }
  } catch (std::exception &e) {
    std::cerr << "convert_vec: impossível converter string para float\n";
    throw e;
  }
  return *target;
}

// template <typename T>
// void print_vec(std::vector<T> &vec, std::ostream &os) {
//   os << "[ ";
//   for (T& elem : vec)
//     os << elem << " ";
//   os << "]" << std::endl;
// }
