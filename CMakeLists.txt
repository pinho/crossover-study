cmake_minimum_required(VERSION 3.5)

project(CrossoverStudy
  VERSION 1.0.2
  LANGUAGES CXX
  DESCRIPTION "Estudos com operadores de crizamento em algoritmo genéticos em otimização combinatória")
  
set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

# Definições sobre o arquivo principal, os problemas e a alvo principal.
# Nome do executavel a ser gerado é o nome do parojeto em lowercase.
string(TOLOWER ${PROJECT_NAME} main_target )
message(STATUS "Main Target: " ${main_target})

# Add/Compile sources to binaries
add_subdirectory(src)

# Compile unit tests
if(BUILD_TESTING)
  enable_testing()
  message(STATUS "Build of unit tests enabled")
  add_subdirectory(test)
endif()
