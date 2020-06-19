cmake_minimum_required(VERSION 3.10)

# Crossover Study for Maximum Clique
project(CrossoverStudy-MC LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} main_target)

include_directories(../../include)
link_libraries(core-ga core-utils vsqlitepp)
# add_compile_options(-Wall -Wunused -Wextra)

add_executable(${main_target}
  main.cxx
  maximum_clique_problem.cxx)

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_BINARYDIR})