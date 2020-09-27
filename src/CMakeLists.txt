cmake_minimum_required(VERSION 3.10)

# Adiciona algumas configurações comuns a todos os subprojetos
include_directories(../include)
add_compile_options("-Wall" "-Wstack-protector")
link_libraries(core-ga core-utils vsqlitepp cliargs)

# Diretórios de códigos fonte
add_subdirectory(maximum_clique)
add_subdirectory(multidimensional_knapsack)
add_subdirectory(set_covering)
add_subdirectory(steiner_tree)
