cmake_minimum_required(VERSION 3.10)
project(SteinerTree LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_executable(steinertree
  main.cpp
  steiner_tree.cpp
  steiner_tree_model.cpp
  minimum_spanning_tree.cpp)

target_include_directories(steinertree PRIVATE ../../include)
target_link_libraries(steinertree PRIVATE GA CLI utils vsqlitepp)

install(TARGETS steinertree DESTINATION ${CMAKE_INSTALL_BINARYDIR})
