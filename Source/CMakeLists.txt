cmake_minimum_required(VERSION 3.6)

find_library(PEO NAMES eo libeo HINTS ../lib64)
find_library(PEOUTILS NAMES eoutils libeoutils HINTS ../lib64)

if(NOT PEO OR NOT PEOUTILS)
  message(FATAL_ERROR "ParadisEO libraries not found")
else()
  message(STATUS "ParadisEO-EO Library: " ${PEO})
  message(STATUS "ParadisEO-EOUtils Library: " ${PEOUTILS})
endif()

# É considerado que o vsqlite++ foi instalado externamente
find_library(VSQL NAMES vsqlitepp libvsqlitepp)
if (VSQL)
  message(STATUS "VSQLite++ library found: " ${VSQL})
else()
  message(FATAL_ERROR "VSQLite++ not found")
endif()

include_directories(../include)

# Arquivo da biblioteca libGA.a que implementa funções relacionadas a algoritos
# genéticos e linka com as bibliotecas do ParadisEO
file(GLOB GA_SOURCES ga/*.cpp)
add_library(GA ${GA_SOURCES})
target_link_libraries(GA eo eoutils)

# Biblioteca libDB.so: implementa funções de comunicação com o banco de dados
# usando a biblioteca vsqlite++
# file(GLOB DB_SOURCES db/*.cpp)
# add_library(DB ${DB_SOURCES})
# target_link_libraries(DB vsqlitepp)

# Arquivos fonte de cada problema abordado na pesquisa
file(GLOB SC_SOURCES sc/*.cxx)
file(GLOB MC_SOURCES mc/*.cxx)
file(GLOB MK_SOURCES mk/*.cxx)
file(GLOB ST_SOURCES st/*.cxx)

link_libraries(vsqlitepp)

# Cada problema é compilado na sua própria biblioteca
add_library(SC SHARED ${SC_SOURCES})
add_library(MC SHARED ${MC_SOURCES})
add_library(MK SHARED ${MK_SOURCES})
add_library(ST SHARED ${ST_SOURCES})

add_executable(crossover-rsch main.cxx)
target_link_libraries(crossover-rsch SC MC MK ST)
