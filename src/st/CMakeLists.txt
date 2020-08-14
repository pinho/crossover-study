cmake_minimum_required(VERSION 3.10)

project(SteinerTree LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

include_directories(../../include)
add_compile_options(-Wunused)

add_executable(steintree_bin
  main.cpp
  steiner_tree.cpp
  minimum_spanning_tree.cpp)
  
target_link_libraries(steintree_bin core-ga core-utils)

install(TARGETS ${main_target} DESTINATION ${CMAKE_INSTALL_BINARYDIR})
