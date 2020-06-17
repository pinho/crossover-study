cmake_minimum_required(VERSION 3.5)

project(CrossoverStudy
  VERSION 1.3.0
  LANGUAGES CXX)
  
## Usando padrão C++ 17
set(CMAKE_CXX_STANDARD 17)

# Bibliotecas construídas localmente
add_subdirectory(include/core)

# Cada problema tem um projeto próprio implementando um executável para cada
# problema abordado na pesquisa
add_subdirectory(source/mc) # clique máximo
# add_subdirectory(sc) # cobertura de conjuntos
# add_subdirectory(st) # Árvore de Steiner
# add_subdirectory(mk) # mochila multidimensional

