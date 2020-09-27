cmake_minimum_required(VERSION 3.10)

# procurando pelas bibliotecas do ParadisEO
find_library(PEO NAMES eo libeo HINTS ../../lib64)
find_library(PEOUTILS NAMES eoutils libeoutils HINTS ../../lib64)

if(NOT PEO OR NOT PEOUTILS)
  message(FATAL_ERROR "ParadisEO libraries not found")
else()
  message(STATUS "ParadisEO-EO: " ${PEO})
  message(STATUS "ParadisEO-EOUtils: " ${PEOUTILS})
endif()

include_directories(../)

# Biblioteca de interface de linha de comandos
file(GLOB CLI_SOURCES cli/*.cpp)
add_library(cliargs SHARED ${CLI_SOURCES})

# Biblioteca para o Algoritmo genético
file(GLOB GA_SOURCES ga/*.cpp)
add_library(core-ga ${GA_SOURCES})
target_link_libraries(core-ga ${PEO} ${PEOUTILS})

# Biblioteca de utilitários
file(GLOB UTILS_SOURCES utils/*.cpp)
add_library(core-utils ${UTILS_SOURCES})

# Regras de instalação das bibliotecas
install(TARGETS core-ga core-utils
        DESTINATION ${CMAKE_INSTALL_LIBDIR})
