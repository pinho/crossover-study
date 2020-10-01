cmake_minimum_required(VERSION 3.10)
project(MaxClique LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} main_target)

add_executable(${main_target}
  main.cxx
  maximum_clique_problem.cxx
  mcp_database.cxx)

target_include_directories(${main_target} PRIVATE ../../include)
target_link_libraries(${main_target} PRIVATE core-ga core-utils vsqlitepp cliargs)

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
