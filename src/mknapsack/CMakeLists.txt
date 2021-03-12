cmake_minimum_required(VERSION 3.15)
project(MultiKnap)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_executable(mkanpsack
  main.cxx
  mknap_problem.cxx
  mknap_table.cxx )

install(TARGETS mknapsack DESTINATION ${CMAKE_INSTALL_BINARYDIR})
