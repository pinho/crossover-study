cmake_minimum_required(VERSION 3.14)
project(SetCovering LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

string(TOLOWER ${PROJECT_NAME} executable_name)

include(GNUInstallDirs)
include_directories(../../include)
add_compile_options(-Wunused)

add_executable(${executable_name}
  main.cpp
  scp_matrix.cpp
  set_covering_problem.cpp
)

target_link_libraries(${executable_name} core-ga core-utils vsqlitepp)
install(TARGETS ${executable_name} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
