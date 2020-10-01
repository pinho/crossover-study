cmake_minimum_required(VERSION 3.14)
project(SetCovering LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} executable_name)

add_executable(${executable_name}
  main.cpp
  scp_matrix.cpp
  scp_table.cpp
  set_covering_problem.cpp
  genetic_algorithm_scp.cpp
)

install(TARGETS ${executable_name} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
