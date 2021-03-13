cmake_minimum_required(VERSION 3.10)
project(MaxClique LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
string(TOLOWER ${PROJECT_NAME} main_target)

add_executable(${main_target}
  main.cpp
  maximum_weighted_clique_problem.cpp
  mcp_database.cpp)

target_include_directories(${main_target} PRIVATE ../../include)
target_link_libraries(${main_target} PRIVATE GA CLI utils vsqlitepp)

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
