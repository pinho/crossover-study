cmake_minimum_required(VERSION 3.15)
project(CrossoverResearch VERSION 0.1)

# Usando C++17
set(CMAKE_CXX_STANDARD 17)
# Define o diretório padrão de instalação como o diretório raíz do projeto para fins de testes
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

add_subdirectory(cr)

install(TARGETS ccrio ccrconfig
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)