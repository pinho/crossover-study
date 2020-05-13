cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

find_library(PEO NAMES eo libeo HINTS /usr/local/lib64)
find_library(PEOUTILS NAMES eoutils libeoutils HINTS /usr/local/lib64)
find_library(VSQL NAMES vsqlitepp libvsqlitepp)

if(NOT PEO OR NOT PEOUTILS)
  message(FATAL_ERROR "ParadisEO libraries not found")
else()
  message("-- ParadisEO Library: " ${PEO})
  message("-- ParadisEO Library: " ${PEOUTILS})
endif()

if (VSQL)
    message("-- VSQLite++ library found: " ${VSQL})
else()
    message(FATAL_ERROR "VSQLite++ not found")
endif()

# Arquivos fonte
file(GLOB GA_SOURCES ga/*.cpp)
file(GLOB IO_SOURCES io/*.cpp)

# Arquivos de cabeçalho
file(GLOB GA_HEADERS ga/*.h)
file(GLOB IO_HEADERS io/*.h)
file(GLOB CLI_HEADERS cli/*.h)

# Compilação e linkagem
add_library(ga ${GA_SOURCES})
target_link_libraries(ga ${PEO} ${PEOUTILS})
add_library(io ${IO_SOURCES})

# Add shared library for db
add_library(db db/database_entry.cpp)
target_link_libraries(db vsqlitepp)
target_compile_options(db PUBLIC -Wall -Wextra)

# Regras de instalação
install(TARGETS ga io db DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

if(INSTALL_HEADERS)
  install(FILES ${GA_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/myresearch/ga)
  install(FILES ${IO_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/myresearch/io)
  install(FILES ${CLI_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/myresearch/cli)
endif()