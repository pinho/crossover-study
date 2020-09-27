cmake_minimum_required(VERSION 3.10)
project(SteinerTree LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_executable(steintree
  main.cpp
  steiner_tree.cpp
  steiner_tree_table.cpp
  minimum_spanning_tree.cpp)

install(TARGETS steintree DESTINATION ${CMAKE_INSTALL_BINARYDIR})
