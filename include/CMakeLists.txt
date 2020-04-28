cmake_minimum_required(VERSION 3.5)

find_library(PEO NAMES eo libeo)
find_library(PEOUTILS NAMES eoutils libeoutils)

if(NOT PEO OR NOT PEOUTILS)
  message(FATAL_ERROR "ParadisEO libraries not found")
else()
  message("-- ParadisEO Library: " ${PEO})
  message("-- ParadisEO Library: " ${PEOUTILS})
endif()

file(GLOB CONFIG_SOURCES config/*.cpp)
file(GLOB GA_SOURCES ga/*.cpp)
file(GLOB IO_SOURCES io/*.cpp)

file(GLOB CONFIG_HEADERS config/*.h)
file(GLOB GA_HEADERS ga/*.h)
file(GLOB IO_HEADERS io/*.h)

add_library(config ${CONFIG_SOURCES})
target_link_libraries(config yaml-cpp)

add_library(ga ${GA_SOURCES})
target_link_libraries(ga ${PEO} ${PEOUTILS})

add_library(io ${IO_SOURCES})