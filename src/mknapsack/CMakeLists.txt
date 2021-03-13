cmake_minimum_required(VERSION 3.15)
project(MultiKnap)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_executable(mknapsack
  main.cpp
  mknap_problem.cpp
  mknap_model.cpp)

target_include_directories(mknapsack PRIVATE ../../include)
target_link_libraries(mknapsack PRIVATE GA CLI utils vsqlitepp)

install(TARGETS mknapsack DESTINATION ${CMAKE_INSTALL_BINARYDIR})
