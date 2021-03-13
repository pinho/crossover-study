cmake_minimum_required(VERSION 3.10)

add_executable(run run.cpp)
install(TARGETS run DESTINATION ${CMAKE_INSTALL_BINARYDIR})

# Diretórios de códigos fonte
add_subdirectory(maxclique)
add_subdirectory(mknapsack)
add_subdirectory(setcovering)
add_subdirectory(steinertree)
