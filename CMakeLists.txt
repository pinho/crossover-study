cmake_minimum_required(VERSION 3.15)

project(CrossoverResearch VERSION 0.1.0)
set(CXX_STANDARD 17)
include(GNUInstallDirs)

# Diretório do executável cr (comparison runner)
# executável que roda o algoritmo
add_subdirectory(cr)

# Regras de instalação
# install(TARGETS ga problems DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
# install(TARGETS cr DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)