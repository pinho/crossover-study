cmake_minimum_required(VERSION 3.15)
project(CrossoverResearch VERSION 0.1)

# Usando C++17
set(CMAKE_CXX_STANDARD 17)
# Setting directories
#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}) # diretório de instalação
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR}) # diretório raíz do projeto
set(CCR_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ccr) # diretório ccr

add_subdirectory(include/ccr)
add_subdirectory(test)
