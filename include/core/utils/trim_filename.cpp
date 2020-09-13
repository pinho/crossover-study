#include "trim_filename.h"

/**
 * Corta o caminho do arquivo reduzindo-o a somente o
 * nome do arquivo */
const char* trim_filename(const char *filename) {
  std::string str_filename(filename);
  return (split(str_filename, '/').end()-1)->c_str();
}
