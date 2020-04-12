cmake_minimum_required(VERSION 3.15)
project(CrossoverResearch VERSION 0.1)

# Usando C++17
set(CMAKE_CXX_STANDARD 17)
# Define o diretório padrão de instalação como o diretório raíz do projeto para fins de testes
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(ccr)

# Install the executable of the genetic algorithm
install(TARGETS garun DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# Install static libraries
install(TARGETS ccrio ccrconfig DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
# Install headers -- defined in cmake command (use -DINSTALL_HEADERS=ON)
if(INSTALL_HEADERS)
    install(
        DIRECTORY ${CMAKE_SOURCE_DIR}/ccr/include/ccr 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    )
endif()

