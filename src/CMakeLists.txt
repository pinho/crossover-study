cmake_minimum_required(VERSION 3.10)

# Adiciona algumas configurações comuns a todos os subprojetos
include_directories(../include)
add_compile_options("-Wall" "-Wstack-protector")
link_libraries(GA core-utils vsqlitepp cliargs)

# Diretórios de códigos fonte
add_subdirectory(maxclique)
add_subdirectory(mknapsack)
add_subdirectory(setcovering)
add_subdirectory(steinertree)
