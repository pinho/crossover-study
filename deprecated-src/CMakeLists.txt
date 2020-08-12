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
include_directories(./)

# Exportando o número de versão para um arquivo
configure_file(${CMAKE_SOURCE_DIR}/VERSION.in 
               ${CMAKE_SOURCE_DIR}/src/version.h)

# Arquivos fonte
file(GLOB GA_SOURCES ga/*.cpp)
file(GLOB IO_SOURCES io/*.cpp)
# file(GLOB DB_SOURCES db/*.cpp)

# Arquivos de cabeçalho
file(GLOB GA_HEADERS ga/*.h)
file(GLOB IO_HEADERS io/*.h)
file(GLOB DB_HEADERS db/*.hpp)
file(GLOB CLI_HEADERS cli/*.h)

# Compilação e linkagem
add_library(ga ${GA_SOURCES})
target_link_libraries(ga ${PEO} ${PEOUTILS})

add_library(io ${IO_SOURCES})

# Regras de instalação
install(TARGETS ga io DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# A opção de instalar os headers deve ser definida no comando cmake
# usando: cmake -DINSTALL_HEADERS=ON
if(INSTALL_HEADERS)
  install(FILES ${GA_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/myresearch/ga)
  install(FILES ${IO_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/myresearch/io)
  install(FILES ${CLI_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/myresearch/cli)
endif()

file(GLOB SCP_SOURCES scp/*.cpp)
file(GLOB MCP_SOURCES mcp/*.cpp)
file(GLOB MKP_SOURCES mkp/*.cpp)
# file(GLOB STP_SOURCES stp/*.cpp)

include_directories(../include)

add_library(problems STATIC ${SCP_SOURCES} ${MCP_SOURCES} ${MKP_SOURCES})
target_link_libraries(problems io ga)

add_executable(${main_target} main.cxx problem_fabric.cxx)
target_link_libraries(${main_target} problems vsqlitepp)

install(TARGETS ${main_target} problems
        RUNTIME
          DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE
          DESTINATION ${CMAKE_INSTALL_LIBDIR})
